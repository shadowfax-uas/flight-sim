#include "TelemetryReplay.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <limits>

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
                std::cerr << "Failed to parse double from value: " << text << "\n";
                return std::nullopt;
            }
            return value;
    }
    catch (const std::invalid_argument& error) {
        std::cerr << "Invalid argument error while parsing double from value: " << text << "\n";
        return std::nullopt;
    }
    catch (const std::out_of_range& error) {
        std::cerr << "Out of range error while parsing double from value: " << text << "\n";
        return std::nullopt;
    }
    }

    std::optional<std::size_t> parseStrictFrame(
        const std::string& text
    ) {
        if (text.empty()) {
            std::cerr << "Failed to parse frame from value: " << text << "\n";
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
            std::cerr << "Failed to parse frame from value: " << text << "\n";
            return std::nullopt;
        }
        try {
            std::stoull(text);
            return static_cast<std::size_t>(std::stoull(text));
        }
        catch (const std::invalid_argument& error) {
            std::cerr << "Invalid argument error while parsing frame from value: " << text << "\n";
            return std::nullopt;
        }
        catch (const std::out_of_range& error) {
            std::cerr << "Out of range error while parsing frame from value: " << text << "\n";
            return std::nullopt;
        }
    }
}

bool TelemetryReplay::load(const std::string& filename) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        return false;
    }

    try {
        records.clear();
        currentIndex = 0;

        std::string line;
        std::getline(inputFile, line);

        while (std::getline(inputFile, line)) {
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

            std::optional<VehicleState> vehicleState = stateFromString(state);
            if (!vehicleState) {
                records.clear();
                return false;
            }

            // Validate values before using in the TelemetryRecord constructor

            std::optional<std::size_t> parsedFrame = parseStrictFrame(frame);
            if (!parsedFrame) {
                records.clear();
                return false;
            }

            std::optional<double> elapsedTimeValue = parseStrictDouble(elapsedTime);
            std::optional<double> xValue = parseStrictDouble(x);
            std::optional<double> yValue = parseStrictDouble(y);
            std::optional<double> altitudeValue = parseStrictDouble(altitude);
            std::optional<double> batteryValue = parseStrictDouble(battery);

            if (!elapsedTimeValue || !xValue || !yValue || !altitudeValue || !batteryValue) {
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
