#ifndef TELEMETRY_SOURCE_HPP
#define TELEMETRY_SOURCE_HPP

#include "TelemetrySample.hpp"

#include <functional>

class TelemetrySource {
    private:
        std::function<void(const TelemetrySample&)> sampleHandler;

    protected:
        void publishSample(const TelemetrySample& sample) const;

    public:
        void setSampleHandler(
            const std::function<void(const TelemetrySample&)>& handler
        );

        virtual ~TelemetrySource() = default;
};

#endif