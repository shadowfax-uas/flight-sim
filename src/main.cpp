#include "Drone.hpp"
#include "Waypoint.hpp"
#include "Mission.hpp"
#include "GPS.hpp"

int main() {
    Drone drone;
    Mission mission;
    GPS gps;

    Sensor& sensor = gps; // Using GPS as a Sensor

    Waypoint waypoint1{10.0, 20.0, 30.0};
    Waypoint waypoint2{15.0, 25.0, 35.0};
    Waypoint waypoint3{20.0, 30.0, 40.0};

    mission.addWaypoint(waypoint1);
    mission.addWaypoint(waypoint2);
    mission.addWaypoint(waypoint3);

    drone.arm();
    drone.printStatus();

    drone.takeOff();
    drone.printStatus();

    sensor.update(drone);
    sensor.printReading();

    mission.execute(drone);
    drone.printStatus();

    sensor.update(drone);
    sensor.printReading();
    
    drone.land();
    drone.printStatus();

    sensor.update(drone);
    sensor.printReading();

    return 0;
}
