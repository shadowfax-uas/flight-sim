#ifndef TELEMETRY_SOURCE_HPP
#define TELEMETRY_SOURCE_HPP

#include "TelemetrySample.hpp"

class TelemetrySource {
    public:
        virtual TelemetrySample sample() const = 0;

        virtual ~TelemetrySource() = default;
};

#endif