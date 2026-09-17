#ifndef MISSION_HPP
#define MISSION_HPP

#include "Waypoint.hpp"
#include "Drone.hpp"

#include <vector>
#include <functional>

class Mission {
private:
    std::vector<Waypoint> waypoints;
public:
    void addWaypoint(const Waypoint& waypoint);
    void execute(
        Drone& drone,
        const std::function<void()>& onStep = {}
    );
};

#endif