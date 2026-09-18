#include "TelemetrySource.hpp"

void TelemetrySource::setSampleHandler(
    const std::function<void(const TelemetrySample&)>& handler
) {
    sampleHandler = handler;
}

void TelemetrySource::publishSample(const TelemetrySample& sample) const {
    if (sampleHandler) {
        sampleHandler(sample);
    }
}