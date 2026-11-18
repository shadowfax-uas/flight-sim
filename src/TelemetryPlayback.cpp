#include <chrono>
#include <thread>
#include <cmath>
#include <stdexcept>

#include "TelemetryPlayback.hpp"

void playTelemetry(
    const std::vector<TelemetryRecord>& records,
    double playbackSpeed,
    const std::function<void(const TelemetryRecord&)>& onRecord
) {
    if (records.empty()) {
        return;
    }
    if (!std::isfinite(playbackSpeed) || playbackSpeed <= 0.0) {
        throw std::invalid_argument("playbackSpeed must be a positive finite value");
    }

    const double firstTimestamp = records.front().elapsedTimeSeconds;

    const auto startTime = std::chrono::steady_clock::now();

    for (const auto& record : records) {
        const double elapsedTime = record.elapsedTimeSeconds - firstTimestamp;
        const double adjustedElapsedTime = elapsedTime / playbackSpeed;

        const auto targetTime = startTime + std::chrono::duration<double>(adjustedElapsedTime);
        std::this_thread::sleep_until(targetTime);

        onRecord(record);
    }
}