#ifndef DRONE_HPP
#define DRONE_HPP

#include "Waypoint.hpp"
#include "VehicleState.hpp"

#include <functional>

class Drone {
private:
    double simulationTimeSeconds;
    double x;
    double y;
    double altitude;
    double speed;
    double batteryLevel;
    double batteryConsumptionRate;
    VehicleState state;
public:
    Drone();
    double getSimulationTimeSeconds() const { return simulationTimeSeconds; }
    double getX() const { return x; }
    double getY() const { return y; }
    double getAltitude() const { return altitude; }
    double getSpeed() const { return speed; }
    double getBatteryLevel() const { return batteryLevel; }
    VehicleState getState() const { return state; }
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