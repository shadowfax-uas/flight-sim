#include "FlightRecorder.hpp"
#include "MockTelemetrySource.hpp"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <format>
#include <iostream>
#include <string>

int main() {
    auto timestamp = std::chrono::system_clock::now();
    std::time_t epochTime = std::chrono::system_clock::to_time_t(timestamp);

    std::filesystem::create_directories("logs");

    std::string logFilename = std::format("logs/stream_{}.csv", epochTime);

    std::string sessionId = std::format("stream-{}", epochTime);

    MockTelemetrySource telemetrySource;

    FlightRecorder flightRecorder(
        sessionId,
        "mock-vehicle-01",
        FlightSource::Simulator,
        epochTime,
        logFilename
    );


    telemetrySource.setSampleHandler(
        [&flightRecorder](const TelemetrySample& sample) {
            flightRecorder.record(sample);
        }
    );

    if (!flightRecorder.isOpen()) {
        std::cerr << "Failed to open telemetry file for writing.\n";
        return 1;
    }

    const FlightSession& flightSession = flightRecorder.getSession();

    std::cout << "Starting mock telemetry stream...\n";

    telemetrySource.run();

    std::cout << "Mock telemetry stream complete.\n";

    std::time_t flightEndTime = 
        std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now()
        );

    flightRecorder.endSession(flightEndTime);

    std::cout
        << "Telemetry records stored: "
        << flightSession.getTelemetryRecords().size()
        << "\n";

    std::cout
        << "Log file: "
        << logFilename
        << "\n";

    return 0;
}