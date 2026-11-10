#include <cmath>

#include "TelemetryStatistics.hpp"

double calculateDurationSeconds(const std::vector<TelemetryRecord>& records) {
    if (records.empty()) {
        return 0.0;
    }
    if (records.size() == 1) {
        return 0.0;
    }
    return records.back().elapsedTimeSeconds - records.front().elapsedTimeSeconds;
}

double calculateDistanceTraveled(const std::vector<TelemetryRecord>& records) {
    if (records.size() < 2) {
        return 0.0;
    }

    double totalDistance = 0.0;

    for (std::size_t i = 1; i < records.size(); ++i) {
        const auto& previous = records[i-1];
        const auto& current = records[i];
        double dx = current.x - previous.x;
        double dy = current.y - previous.y;
        totalDistance += std::hypot(dx, dy);
    }
    return totalDistance;
}

std::optional<double> calculateMaxAltitude(const std::vector<TelemetryRecord>& records) {
    if (records.empty()) {
        return std::nullopt;
    }

    double maxAltitude = records.front().altitude;
    for (const auto& record : records) {
        if (record.altitude > maxAltitude) {
            maxAltitude = record.altitude;
        }
    }
    return maxAltitude;
}

std::optional<double> calculateBatteryConsumed(const std::vector<TelemetryRecord>& records) {
    if (records.size() < 1) {
        return std::nullopt;
    }
    if (records.size() == 1) {
        return 0.0;
    }

    double batteryConsumed = records.front().batteryLevel - records.back().batteryLevel;
    return batteryConsumed;
}