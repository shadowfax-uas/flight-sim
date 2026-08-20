#ifndef DRONE_HPP
#define DRONE_HPP
#include "Waypoint.hpp"

enum class DroneState {
    Grounded,
    Armed,
    Flying
};

class Drone {
private:
    double x;
    double y;
    double altitude;
    double batteryLevel;
    DroneState state;
public:
    Drone();
    void arm();
    void takeOff();
    void land();
    void flyTo(const Waypoint& waypoint);
    void printStatus() const;
};

#endif