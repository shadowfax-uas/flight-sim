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
    double speed;
    double batteryLevel;
    double batteryConsumptionRate;
    DroneState state;
public:
    Drone();
    double getX() const { return x; }
    double getY() const { return y; }
    double getAltitude() const { return altitude; }
    double getSpeed() const { return speed; }
    double getBatteryLevel() const { return batteryLevel; }
    DroneState getState() const { return state; }
    void arm();
    void takeOff();
    void land();
    void flyTo(const Waypoint& waypoint);
    void printStatus() const;
};

#endif