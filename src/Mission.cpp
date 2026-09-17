#include "Mission.hpp"

void Mission::addWaypoint(const Waypoint& waypoint) {
    waypoints.push_back(waypoint);
}

void Mission::execute(
    Drone& drone,
    const std::function<void()>& onStep) {
    for (const Waypoint& waypoint : waypoints) {
        drone.flyTo(waypoint, onStep);
    }
}
