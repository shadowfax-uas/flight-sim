#include "TelemetryRecorder.hpp"

#include <iostream>

TelemetryRecorder::TelemetryRecorder(const std::string& filename)
    : outputFile(filename) {
    if (outputFile.is_open()) {
        outputFile << "frame,elapsedTimeSeconds,x,y,altitude,battery,state\n";
    }
}

bool TelemetryRecorder::isOpen() const {
    return outputFile.is_open();
}

std::string TelemetryRecorder::stateToString(VehicleState state) const {
    switch (state) {
        case VehicleState::Grounded: return "Grounded";
        case VehicleState::Armed: return "Armed";
        case VehicleState::Flying: return "Flying";
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
        << record.elapsedTimeSeconds << ","
        << record.x << ","
        << record.y << ","
        << record.altitude << ","
        << record.batteryLevel << ","
        << stateToString(record.state) << "\n";
    
}
