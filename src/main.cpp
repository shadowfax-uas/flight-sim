#include "Drone.hpp"
#include "Waypoint.hpp"
#include "Mission.hpp"
#include "GPS.hpp"
#include "IMU.hpp"
#include "Radar.hpp"
#include "SensorManager.hpp"
#include "TelemetryRecorder.hpp"
#include "TelemetryReplay.hpp"

#include <memory>
#include <chrono>
#include <format>
#include <filesystem>
#include <iostream>

int main() {
    auto timestamp = std::chrono::system_clock::now();
    std::time_t epochTime = std::chrono::system_clock::to_time_t(timestamp);

    std::filesystem::create_directories("logs");

    std::string logFilename = std::format("logs/flight_{}.csv", epochTime);

    Drone drone;
    Mission mission;
    SensorManager sensorManager;

    {
        TelemetryRecorder telemetryRecorder(logFilename);
        

        if (!telemetryRecorder.isOpen()) {
            std::cerr << "Failed to open telemetry file for writing.\n";
            return 1;
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

        telemetryRecorder.record(drone);

        drone.arm();
        telemetryRecorder.record(drone);

        drone.takeOff();
        telemetryRecorder.record(drone);
        drone.printStatus();

        sensorManager.updateAll(drone);
        sensorManager.printAll();

        mission.execute(drone);
        telemetryRecorder.record(drone);
        drone.printStatus();

        sensorManager.updateAll(drone);
        sensorManager.printAll();
        
        drone.land();
        telemetryRecorder.record(drone);
        drone.printStatus();

        sensorManager.updateAll(drone);
        sensorManager.printAll();
    }

    TelemetryReplay replay;

    if (!replay.load(logFilename)) {
        std::cerr << "Failed to load telemetry file for replay.\n";
        return 1;
    }

    std::cout << "\nLoaded " 
              << replay.getRecordCount() 
              << " telemetry records for replay.\n";


    const TelemetryRecord& record = replay.current();

    std::cout << "Frame: " << record.frameNumber << "\n";
    std::cout << "Position: " 
              << record.x << ", " 
              << record.y << "," 
              << record.altitude << "\n";

    while (replay.next()) {
        const TelemetryRecord& record = replay.current();
        std::cout << "Frame: " << record.frameNumber << "\n";
        std::cout << ": " 
                  << record.x << ", " 
                  << record.y << "," 
                  << record.altitude << "\n";
    }

    return 0;
}
