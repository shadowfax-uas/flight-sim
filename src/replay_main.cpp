#include "TelemetryReplay.hpp"
#include "NumericParsing.hpp"
#include "TelemetryStatistics.hpp"
#include "TelemetryPlayback.hpp"

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: flight-replay <telemetry_file> [playback_speed]\n";
        return 1;
    }

    std::string filename = argv[1];

    double playbackSpeed = 1.0; // Default playback speed

    if (argc == 3) {
        // Only parse if the user provided a speed argument
        auto parsedSpeed = parsing::parseStrictDouble(argv[2]);

        if (!parsedSpeed || *parsedSpeed <= 0.0) {
            std::cerr << "Invalid playback speed: " << argv[2] << "\n";
            return 1;
        }

        playbackSpeed = *parsedSpeed;
    }

    TelemetryReplay replay;

    if (!replay.load(filename)) {
        std::cerr << "Failed to load telemetry file: " << filename << "\n";
        return 1;
    }

    std::cout << "Loaded " << replay.getRecordCount() << " telemetry records.\n";

    const auto& records = replay.getRecords();

    double distance = calculateDistanceTraveled(records);
    std::cout << "Total distance traveled: " << distance << " meters\n";

    double duration = calculateDurationSeconds(records);
    std::cout << "Total duration: " << duration << " seconds\n";

    std::optional<double> maxAltitude = calculateMaxAltitude(records);
    if (maxAltitude) {
        std::cout << "Maximum altitude: " << *maxAltitude << " meters\n";
    } else {
        std::cout << "Maximum altitude: N/A\n";
    }

    std::optional<double> batteryConsumed = calculateBatteryConsumed(records);
    if (batteryConsumed) {
        std::cout << "Battery consumed: " << *batteryConsumed << "%\n";
    } else {
        std::cout << "Battery consumed: N/A\n";
    }

    std::cout << "Playback speed: " << playbackSpeed << "x\n";
    playTelemetry(records, playbackSpeed, [](const TelemetryRecord& record) {
        std::cout
            << "[t=" << record.elapsedTimeSeconds << "s] "
            << "Frame " << record.frameNumber
            << " | Altitude: " << record.altitude
            << " | Battery: " << record.batteryLevel
            << "%\n" << std::flush;
    });
    return 0;
}
