#include "Drone.hpp"
#include "Waypoint.hpp"
#include "Mission.hpp"
#include "GPS.hpp"
#include "IMU.hpp"
#include "Radar.hpp"
#include "SensorManager.hpp"
#include "FlightRecorder.hpp"
#include "SimulatedDroneSource.hpp"

#include <memory>
#include <chrono>
#include <format>
#include <filesystem>
#include <iostream>
#include <ctime>
#include <string>

int main() {
    auto timestamp = std::chrono::system_clock::now();
    std::time_t epochTime = std::chrono::system_clock::to_time_t(timestamp);

    std::filesystem::create_directories("logs");

    std::string logFilename = std::format("logs/flight_{}.csv", epochTime);

    std::string sessionId = std::format("sim-{}", epochTime);

    Drone drone;
    SimulatedDroneSource telemetrySource(drone);
    Mission mission;
    SensorManager sensorManager;

    FlightRecorder flightRecorder(
        sessionId,
        "sim-drone-01",
        FlightSource::Simulator,
        epochTime,
        logFilename
    );

    const FlightSession& flightSession = flightRecorder.getSession();

    if (!flightRecorder.isOpen()) {
        std::cerr << "Failed to open telemetry file for writing.\n";
        return 1;
    }

    // Sanity check for functionality
    if (!flightSession.isComplete()) {
        std::cout << "Flight session is ongoing.\n";
    } else {
        std::cout << "Flight session has ended.\n";
    }

    sensorManager.addSensor(std::make_unique<GPS>());
    sensorManager.addSensor(std::make_unique<IMU>());
    sensorManager.addSensor(std::make_unique<Radar>());

    Waypoint waypoint1{10.0, 20.0, 30.0};
    Waypoint waypoint2{15.0, 25.0, 35.0};
    Waypoint waypoint3{20.0, 30.0, 40.0};

    mission.addWaypoint(waypoint1);
    mission.addWaypoint(waypoint2);
    mission.addWaypoint(waypoint3);

    flightRecorder.record(telemetrySource.sample());

    drone.arm();
    flightRecorder.record(telemetrySource.sample());

    drone.takeOff();
    flightRecorder.record(telemetrySource.sample());
    drone.printStatus();

    sensorManager.updateAll(drone);
    sensorManager.printAll();

    mission.execute(drone);
    flightRecorder.record(telemetrySource.sample());
    drone.printStatus();

    sensorManager.updateAll(drone);
    sensorManager.printAll();
    
    drone.land();
    flightRecorder.record(telemetrySource.sample());
    drone.printStatus();

    sensorManager.updateAll(drone);
    sensorManager.printAll();

    std::time_t flightEndTime = 
        std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now()
        );

    flightRecorder.endSession(flightEndTime);

    // Sanity check for functionality
    if (!flightSession.isComplete()) {
        std::cout << "Flight session is ongoing.\n";
    } else {
        std::cout << "Flight session has ended.\n";
    }

    std::cout << "\nFlight session complete:\n";

    std::cout << "Session ID: "
            << flightSession.getSessionId()
            << "\n";

    std::cout << "Vehicle ID: "
            << flightSession.getVehicleId()
            << "\n";

    std::cout << "Start time: "
            << flightSession.getStartTime()
            << "\n";

    if (flightSession.getEndTime()) {
        std::cout << "End time: "
                << flightSession.getEndTime().value()
                << "\n";
    }

    std::cout << "Telemetry records stored: "
            << flightSession.getTelemetryRecords().size()
            << "\n";

    return 0;
}
