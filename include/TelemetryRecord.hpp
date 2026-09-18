#ifndef TELEMETRY_RECORD_HPP
#define TELEMETRY_RECORD_HPP

#include "VehicleState.hpp"

#include <cstddef>

struct TelemetryRecord {
    std::size_t frameNumber;
    double elapsedTimeSeconds;
    double x;
    double y;
    double altitude;
    double batteryLevel;
    VehicleState state;
};

#endif