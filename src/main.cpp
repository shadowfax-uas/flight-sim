#include "Drone.hpp"
#include "Waypoint.hpp"

int main() {
    Waypoint waypoint1{10.0, 20.0, 30.0};
    Waypoint waypoint2{15.0, 25.0, 35.0};
    Waypoint waypoint3{20.0, 30.0, 40.0};
    Drone drone;
    drone.flyTo(waypoint1);
    drone.printStatus();
    drone.flyTo(waypoint2);
    drone.printStatus();
    drone.flyTo(waypoint3);
    drone.printStatus();
    return 0;
}
