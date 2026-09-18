#ifndef TELEMETRY_SAMPLE_HPP
#define TELEMETRY_SAMPLE_HPP

#include "VehicleState.hpp"

struct TelemetrySample {
    double elapsedTimeSeconds;
    double x;
    double y;
    double altitude;
    double batteryLevel;
    VehicleState state;
};

#endif