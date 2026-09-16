#ifndef TELEMETRY_SAMPLE_HPP
#define TELEMETRY_SAMPLE_HPP

#include "Drone.hpp"

struct TelemetrySample {
    double x;
    double y;
    double altitude;
    double batteryLevel;
    DroneState state;
};

#endif