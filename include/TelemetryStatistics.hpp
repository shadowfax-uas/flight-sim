#pragma once

#include <vector>
#include "TelemetryRecord.hpp"

double calculateDurationSeconds(
    const std::vector<TelemetryRecord>& records
);

double calculateDistanceTraveled(
    const std::vector<TelemetryRecord>& records
);