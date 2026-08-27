#ifndef TELEMETRY_RECORD_HPP
#define TELEMETRY_RECORD_HPP

#include "Drone.hpp"

#include <cstddef>

struct TelemetryRecord {
    std::size_t frameNumber;
    double x;
    double y;
    double altitude;
    double batteryLevel;
    DroneState state;
};

#endif