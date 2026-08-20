#include "Drone.hpp"
#include "Waypoint.hpp"
#include "Mission.hpp"

int main() {
    Drone drone;
    Mission mission;

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

    mission.execute(drone);
    drone.printStatus();
    
    drone.land();
    drone.printStatus();
    return 0;
}
