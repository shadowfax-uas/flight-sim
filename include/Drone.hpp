#ifndef DRONE_HPP
#define DRONE_HPP

#include "Waypoint.hpp"

#include <functional>

enum class DroneState {
    Grounded,
    Armed,
    Flying
};

class Drone {
private:
    double simulationTimeSeconds;
    double x;
    double y;
    double altitude;
    double speed;
    double batteryLevel;
    double batteryConsumptionRate;
    DroneState state;
public:
    Drone();
    double getSimulationTimeSeconds() const { return simulationTimeSeconds; }
    double getX() const { return x; }
    double getY() const { return y; }
    double getAltitude() const { return altitude; }
    double getSpeed() const { return speed; }
    double getBatteryLevel() const { return batteryLevel; }
    DroneState getState() const { return state; }
    void arm();
    void takeOff();
    void land();
    void flyTo(
        const Waypoint& waypoint,
        const std::function<void()>& onStep = {}
    );
    void printStatus() const;
};

#endif