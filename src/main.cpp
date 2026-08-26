#include "Drone.hpp"
#include "Waypoint.hpp"
#include "Mission.hpp"
#include "GPS.hpp"
#include "IMU.hpp"
#include "Radar.hpp"
#include "Sensor.hpp"

#include <memory>
#include <vector>

int main() {
    Drone drone;
    Mission mission;
    std::vector<std::unique_ptr<Sensor>> sensors;

    sensors.push_back(std::make_unique<GPS>());
    sensors.push_back(std::make_unique<IMU>());
    sensors.push_back(std::make_unique<Radar>());

    Waypoint waypoint1{10.0, 20.0, 30.0};
    Waypoint waypoint2{15.0, 25.0, 35.0};
    Waypoint waypoint3{20.0, 30.0, 40.0};

    mission.addWaypoint(waypoint1);
    mission.addWaypoint(waypoint2);
    mission.addWaypoint(waypoint3);

    drone.arm();
    drone.takeOff();
    drone.printStatus();

    for (const auto& sensor : sensors) {
        sensor->update(drone);
        sensor->printReading();
    }

    mission.execute(drone);
    drone.printStatus();

    for (const auto& sensor : sensors) {
        sensor->update(drone);
        sensor->printReading();
    }
    
    drone.land();
    drone.printStatus();

    for (const auto& sensor : sensors) {
        sensor->update(drone);
        sensor->printReading();
    }

    return 0;
}
