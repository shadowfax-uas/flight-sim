#include "Drone.hpp"
#include <iostream>

Drone::Drone() : x(0), y(0), altitude(0), batteryLevel(100) {}

void Drone::flyTo(const Waypoint& waypoint) {
    x = waypoint.x;
    y = waypoint.y;
    altitude = waypoint.altitude;
    batteryLevel -= 5; // Simulate battery consumption
}

void Drone::printStatus() const {
    std::cout << "Drone position: (" << x << ", " << y << ", " << altitude << ")" << std::endl;
    std::cout << "Battery level: " << batteryLevel << "%" << std::endl;
}