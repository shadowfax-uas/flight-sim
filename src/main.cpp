#include "Drone.hpp"
#include "Waypoint.hpp"
#include "Mission.hpp"
#include "GPS.hpp"
#include "IMU.hpp"
#include "Radar.hpp"
#include "SensorManager.hpp"

#include <memory>

int main() {
    Drone drone;
    Mission mission;
    SensorManager sensorManager;

    sensorManager.addSensor(std::make_unique<GPS>());
    sensorManager.addSensor(std::make_unique<IMU>());
    sensorManager.addSensor(std::make_unique<Radar>());

    Waypoint waypoint1{10.0, 20.0, 30.0};
    Waypoint waypoint2{15.0, 25.0, 35.0};
    Waypoint waypoint3{20.0, 30.0, 40.0};

    mission.addWaypoint(waypoint1);
    mission.addWaypoint(waypoint2);
    mission.addWaypoint(waypoint3);

    drone.arm();
    drone.takeOff();
    drone.printStatus();

    sensorManager.updateAll(drone);
    sensorManager.printAll();

    mission.execute(drone);
    drone.printStatus();

    sensorManager.updateAll(drone);
    sensorManager.printAll();
    
    drone.land();
    drone.printStatus();

    sensorManager.updateAll(drone);
    sensorManager.printAll();

    return 0;
}
