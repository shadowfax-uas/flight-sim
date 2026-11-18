#pragma once

#include <functional>
#include <vector>

#include "TelemetryRecord.hpp"

void playTelemetry(
    const std::vector<TelemetryRecord>& records,
    double playbackSpeed,
    const std::function<void(const TelemetryRecord&)>& onRecord
);