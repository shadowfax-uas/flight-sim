#include "TelemetryRecorder.hpp"

#include <iostream>

TelemetryRecorder::TelemetryRecorder(const std::string& filename)
    : outputFile(filename), 
      nextFrameNumber(0) {
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

void TelemetryRecorder::record(const Drone& drone) {
    if (!outputFile.is_open()) {
        std::cerr << "Telemetry file is not open.\n";
        return;
    }

    TelemetryRecord record{
        nextFrameNumber,
        drone.getX(),
        drone.getY(),
        drone.getAltitude(),
        drone.getBatteryLevel(),
        drone.getState()
    };

    ++nextFrameNumber;

    outputFile
        << record.frameNumber << ","
        << record.x << ","
        << record.y << ","
        << record.altitude << ","
        << record.batteryLevel << ","
        << stateToString(record.state) << "\n";
    
}
