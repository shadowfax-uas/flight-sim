#include "TelemetryReplay.hpp"

#include <fstream>
#include <sstream>

TelemetryReplay::TelemetryReplay() : currentIndex(0) {}

DroneState TelemetryReplay::stateFromString(const std::string& state) const {
    if (state == "Grounded") return DroneState::Grounded;
    if (state == "Armed") return DroneState::Armed;
    if (state == "Flying") return DroneState::Flying;
    return DroneState::Grounded;
}

bool TelemetryReplay::load(const std::string& filename) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        return false;
    }

    records.clear();
    currentIndex = 0;

    std::string line;
    std::getline(inputFile, line);

    while (std::getline(inputFile, line)) {
        std::stringstream lineStream(line);

        std::string frame;
        std::string x;
        std::string y;
        std::string altitude;
        std::string battery;
        std::string state;

        std::getline(lineStream, frame, ',');
        std::getline(lineStream, x, ',');
        std::getline(lineStream, y, ',');
        std::getline(lineStream, altitude, ',');
        std::getline(lineStream, battery, ',');
        std::getline(lineStream, state);

        TelemetryRecord record{
            static_cast<std::size_t>(std::stoull(frame)),
            std::stod(x),
            std::stod(y),
            std::stod(altitude),
            std::stod(battery),
            stateFromString(state)
        };
        records.push_back(record);
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