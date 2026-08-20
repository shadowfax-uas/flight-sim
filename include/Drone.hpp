#ifndef DRONE_HPP
#define DRONE_HPP
#include "Waypoint.hpp"

class Drone {
private:
    // Drone properties and methods
    double x;
    double y;
    double altitude;
    double batteryLevel;
public:
    Drone();
    void flyTo(const Waypoint& waypoint);
    void printStatus() const;
};

#endif // DRONE_HPP