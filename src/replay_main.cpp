#include "TelemetryReplay.hpp"
#include "NumericParsing.hpp"

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: flight-replay <telemetry_file>\n";
        return 1;
    }

    std::string filename = argv[1];

    auto parsedSpeed = parsing::parseStrictDouble(argv[2]);
    
    if (!parsedSpeed.has_value() || parsedSpeed.value() <= 0.0) {
        std::cerr << "Invalid playback speed: " << argv[2] << "\n";
        return 1;
    }
    if (!std::isfinite(parsedSpeed.value())) {
        std::cerr << "Invalid playback speed: " << argv[2] << "\n";
        return 1;
    }
    if (parsedSpeed.value() != 1.0) {
        std::cout << "Playback speed: " << parsedSpeed.value() << "x\n";
    }
    

    TelemetryReplay replay;

    if (!replay.load(filename)) {
        std::cerr << "Failed to load telemetry file: " << filename << "\n";
        return 1;
    }

    std::cout << "Loaded " << replay.getRecordCount() << " telemetry records.\n";

    const double firstTimestamp = replay.current().elapsedTimeSeconds;

    const auto startTime = std::chrono::steady_clock::now();

    do {
        const auto& record = replay.current();

        double replaySeconds = (record.elapsedTimeSeconds - firstTimestamp) / parsedSpeed.value();

        auto scheduledTime = startTime + std::chrono::duration<double>(replaySeconds);

        std::this_thread::sleep_until(scheduledTime);

        std::cout
            << "[t=" << record.elapsedTimeSeconds << "s] "
            << "Frame " << record.frameNumber
            << " | Altitude: " << record.altitude
            << " | Battery: " << record.batteryLevel
            << "%\n" << std::flush;
    } while (replay.next());

    const TelemetryRecord& record = replay.current();
    std::cout << "Frame " << record.frameNumber
              << " [" 
              << record.elapsedTimeSeconds 
              << "s]: "
              << record.x << ", "
              << record.y << ", "
              << record.altitude 
              << "\n";

    while (replay.next()) {
        const TelemetryRecord& record = replay.current();
        std::cout << "Frame " << record.frameNumber
                  << " [" 
                  << record.elapsedTimeSeconds 
                  << "s]: "
                  << record.x << ", "
                  << record.y << ", "
                  << record.altitude << "\n";
    }
    return 0;
}
