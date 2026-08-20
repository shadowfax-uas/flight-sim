#include "Drone.hpp"
#include "Waypoint.hpp"

int main() {
    Waypoint waypoint_1{10.0, 20.0, 30.0};
    Waypoint waypoint_2{15.0, 25.0, 35.0};
    Waypoint waypoint_3{20.0, 30.0, 40.0};
    Drone drone;
    drone.flyTo(waypoint_1);
    drone.printStatus();
    drone.flyTo(waypoint_2);
    drone.printStatus();
    drone.flyTo(waypoint_3);
    drone.printStatus();
    return 0;
}
