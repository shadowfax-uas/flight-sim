#include "TelemetryReplay.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cmath>

TelemetryReplay::TelemetryReplay() : currentIndex(0) {}

std::optional<VehicleState> TelemetryReplay::stateFromString(const std::string& state) const {
    if (state == "Grounded") return VehicleState::Grounded;
    if (state == "Armed") return VehicleState::Armed;
    if (state == "Flying") return VehicleState::Flying;
    return std::nullopt;
}

namespace {
    // Validate that the entire string can be converted to a double
    std::optional<double> parseStrictDouble(
        const std::string& text
    ) { try {
            std::size_t characterConsumed = 0;
            double value = std::stod(text, &characterConsumed);
            if (characterConsumed != text.size()) {
                return std::nullopt;
            }
            if (!std::isfinite(value)) {
                return std::nullopt;
            }
            return value;
    }
    catch (const std::invalid_argument& error) {
        return std::nullopt;
    }
    catch (const std::out_of_range& error) {
        return std::nullopt;
    }
    }

    std::optional<std::size_t> parseStrictFrame(
        const std::string& text
    ) {
        if (text.empty()) {
            return std::nullopt;
        }

        bool onlyDigits = std::all_of(
            text.begin(),
            text.end(),
            [](char character) {
                return character >= '0' && character <= '9';
            }
        );
        if (!onlyDigits) {
            return std::nullopt;
        }
        try {
            unsigned long long value = std::stoull(text);
            if (value > std::numeric_limits<std::size_t>::max()) {
                return std::nullopt;
            }
            return static_cast<std::size_t>(value);
        }
        catch (const std::invalid_argument& error) {
            return std::nullopt;
        }
        catch (const std::out_of_range& error) {
            return std::nullopt;
        }
    }
}

bool TelemetryReplay::load(const std::string& filename) {
    records.clear();
    currentIndex = 0;

    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        return false;
    }

    const std::string expectedHeader = "frame,elapsedTimeSeconds,x,y,altitude,battery,state";

    try {
        std::string line;

        if (!std::getline(inputFile, line)) {
            std::cerr << "Failed to read header\n";
            records.clear();
            return false;
        }
        if (line != expectedHeader) {
            std::cerr << "Invalid header: " << line << "\n";
            records.clear();
            return false;
        }

        std::size_t lineNumber = 1;

        while (std::getline(inputFile, line)) {
            ++lineNumber;

            const auto commaCount = std::count(line.begin(), line.end(), ',');
            
            if (commaCount != 6) {
                std::cerr << "Line " << lineNumber
                          << ": expected 7 columns, found "
                          << (commaCount + 1) << "\n";
                records.clear();
                return false;
            }

            std::stringstream lineStream(line);

            std::string frame;
            std::string elapsedTime;
            std::string x;
            std::string y;
            std::string altitude;
            std::string battery;
            std::string state;

            std::getline(lineStream, frame, ',');
            std::getline(lineStream, elapsedTime, ',');
            std::getline(lineStream, x, ',');
            std::getline(lineStream, y, ',');
            std::getline(lineStream, altitude, ',');
            std::getline(lineStream, battery, ',');
            std::getline(lineStream, state);

            // Validate values before using in the TelemetryRecord constructor

            std::optional<VehicleState> vehicleState = stateFromString(state);
            if (!vehicleState) {
                std::cerr << "Line " << lineNumber << ": invalid state value: " << state << "\n";
                records.clear();
                return false;
            }

            std::optional<std::size_t> parsedFrame = parseStrictFrame(frame);
            if (!parsedFrame) {
                std::cerr << "Line " << lineNumber << ": invalid frame value: " << frame << "\n";
                records.clear();
                return false;
            }

            std::optional<double> elapsedTimeValue = parseStrictDouble(elapsedTime);
            if (!elapsedTimeValue) {
                std::cerr << "Line " << lineNumber << ": invalid elapsedTimeSeconds value: " << elapsedTime << "\n";
                records.clear();
                return false;
            }
            if (*elapsedTimeValue < 0) {
                std::cerr << "Line " << lineNumber << ": elapsedTimeSeconds cannot be negative: " << elapsedTime << "\n";
                records.clear();
                return false;
            }
            if (!records.empty()) {
                const auto& lastRecord = records.back();
                if (*elapsedTimeValue < lastRecord.elapsedTimeSeconds) {
                    std::cerr << "Line " << lineNumber << ": elapsedTimeSeconds moved backward: " << elapsedTime << "\n";
                    records.clear();
                    return false;
                }
            }

            std::optional<double> xValue = parseStrictDouble(x);
            if (!xValue) {
                std::cerr << "Line " << lineNumber << ": invalid x value: " << x << "\n";
                records.clear();
                return false;
            }

            std::optional<double> yValue = parseStrictDouble(y);
            if (!yValue) {
                std::cerr << "Line " << lineNumber << ": invalid y value: " << y << "\n";
                records.clear();
                return false;
            }

            std::optional<double> altitudeValue = parseStrictDouble(altitude);
            if (!altitudeValue) {
                std::cerr << "Line " << lineNumber << ": invalid altitude value: " << altitude << "\n";
                records.clear();
                return false;
            }

            std::optional<double> batteryValue = parseStrictDouble(battery);
            if (!batteryValue) {
                std::cerr << "Line " << lineNumber << ": invalid battery value: " << battery << "\n";
                records.clear();
                return false;
            }
            if (*batteryValue < 0 || *batteryValue > 100) {
                std::cerr << "Line " << lineNumber << ": battery out of range: " << battery << "\n";
                records.clear();
                return false;
            }
            
            TelemetryRecord record{
                parsedFrame.value(),
                elapsedTimeValue.value(),
                xValue.value(),
                yValue.value(),
                altitudeValue.value(),
                batteryValue.value(),
                vehicleState.value()
            };
            records.push_back(record);
        }
    }
    catch (const std::invalid_argument& error) {
        std::cerr << "Invalid argument error while parsing record: " << error.what() << "\n";
        records.clear();
        return false;
    }
    catch (const std::out_of_range& error) {
        std::cerr << "Out of range error while parsing record: " << error.what() << "\n";
        records.clear();
        return false;
    }
    return !records.empty();
}

bool TelemetryReplay::hasRecords() const {
    return !records.empty();
}

std::size_t TelemetryReplay::getRecordCount() const {
    return records.size();
}

const TelemetryRecord& TelemetryReplay::current() const {
    return records.at(currentIndex);
}

bool TelemetryReplay::next() {
    if (currentIndex + 1 < records.size()) {
        ++currentIndex;
        return true;
    }
    return false;
}

bool TelemetryReplay::previous() {
    if (currentIndex > 0) {
        --currentIndex;
        return true;
    }
    return false;
}

bool TelemetryReplay::seek(std::size_t index) {
    if (index < records.size()) {
        currentIndex = index;
        return true;
    }
    return false;
}
