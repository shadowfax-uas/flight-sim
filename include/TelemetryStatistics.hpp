#pragma once

#include <vector>
#include <optional>
#include "TelemetryRecord.hpp"

double calculateDurationSeconds(
    const std::vector<TelemetryRecord>& records
);

double calculateDistanceTraveled(
    const std::vector<TelemetryRecord>& records
);

std::optional<double> calculateMaxAltitude(
    const std::vector<TelemetryRecord>& records
);

std::optional<double> calculateBatteryConsumed(
    const std::vector<TelemetryRecord>& records
);