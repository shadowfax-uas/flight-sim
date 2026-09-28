#include "FlightRecorder.hpp"
#include "MockTelemetrySource.hpp"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <format>
#include <iostream>
#include <string>
#include <thread>

int main() {
    auto timestamp = std::chrono::system_clock::now();
    std::time_t epochTime = std::chrono::system_clock::to_time_t(timestamp);

    std::filesystem::create_directories("logs");

    std::string logFilename = std::format("logs/stream_{}.csv", epochTime);

    std::string sessionId = std::format("stream-{}", epochTime);

    FlightRecorder flightRecorder(
        sessionId,
        "mock-vehicle-01",
        FlightSource::Simulator,
        epochTime,
        logFilename
    );

    MockTelemetrySource telemetrySource;

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

    telemetrySource.start();

    std::cout << "Main thread is still running.\n";

    while (telemetrySource.isRunning()) {
        std::cout << "Main thread: telemetry still arriving...\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(750));
    }

    telemetrySource.wait();

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