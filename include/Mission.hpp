#ifndef MISSION_HPP
#define MISSION_HPP

#include <vector>
#include "Waypoint.hpp"
#include "Drone.hpp"


class Mission {
private:
    std::vector<Waypoint> waypoints;
public:
    void addWaypoint(const Waypoint& waypoint);
    void execute(Drone& drone);
};

#endif