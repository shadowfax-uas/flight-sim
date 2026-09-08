#include "TelemetryRecorder.hpp"

#include <iostream>

TelemetryRecorder::TelemetryRecorder(const std::string& filename)
    : outputFile(filename) {
    if (outputFile.is_open()) {
        outputFile << "frame,x,y,altitude,battery,state\n";
    }
}

bool TelemetryRecorder::isOpen() const {
    return outputFile.is_open();
}

std::string TelemetryRecorder::stateToString(DroneState state) const {
    switch (state) {
        case DroneState::Grounded: return "Grounded";
        case DroneState::Armed: return "Armed";
        case DroneState::Flying: return "Flying";
        default: return "Unknown";
    }
}

void TelemetryRecorder::record(const TelemetryRecord& record) {
    if (!outputFile.is_open()) {
        std::cerr << "Telemetry file is not open.\n";
        return;
    }

    outputFile
        << record.frameNumber << ","
        << record.x << ","
        << record.y << ","
        << record.altitude << ","
        << record.batteryLevel << ","
        << stateToString(record.state) << "\n";
    
}
