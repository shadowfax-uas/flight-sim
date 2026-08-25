#include "Drone.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

Drone::Drone() : x(0), y(0), altitude(0), speed(10), batteryLevel(100), batteryConsumptionRate(0.05), state(DroneState::Grounded) {}

void Drone::arm() {
    if (state == DroneState::Grounded) {
        state = DroneState::Armed;
        std::cout << "Drone armed." << std::endl;
    } else {
        std::cout << "Drone cannot be armed in its current state." << std::endl;
    }
}

void Drone::takeOff() {
    if (state == DroneState::Armed) {
        state = DroneState::Flying;
        altitude = 10.0;
        std::cout << "Drone taking off." << std::endl;
    } else {
        std::cout << "Drone cannot take off in its current state." << std::endl;
    }
}

void Drone::land() {
    if (state == DroneState::Flying) {
        state = DroneState::Grounded;
        altitude = 0.0;
        std::cout << "Drone landing." << std::endl;
    } else {
        std::cout << "Drone cannot land in its current state." << std::endl;
    }
}

void Drone::flyTo(const Waypoint& waypoint) {
    if (state != DroneState::Flying) {
        std::cout << "Drone must be flying to navigate to a waypoint." << std::endl;
        return;
    }

    double deltaX = waypoint.x - x;
    double deltaY = waypoint.y - y;
    double deltaAltitude = waypoint.altitude - altitude;

    double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY + deltaAltitude * deltaAltitude);

    if (distance == 0) {
        std::cout << "Drone is already at the waypoint." << std::endl;
        return;
    }

    if (batteryLevel <= 0) {
        std::cout << "Battery depleted. Drone cannot fly." << std::endl;
        return;
    }

    int steps = static_cast<int>(std::ceil(distance / speed));

    double stepX = deltaX / steps;
    double stepY = deltaY / steps;
    double stepAltitude = deltaAltitude / steps;
    double stepDistance = distance / steps;

    for (int i = 0; i < steps; ++i) {
        x += stepX;
        y += stepY;
        altitude += stepAltitude;
        batteryLevel = std::max(0.0, batteryLevel - stepDistance * batteryConsumptionRate);
        printStatus();
    }

    x = waypoint.x;
    y = waypoint.y;
    altitude = waypoint.altitude;

    std::cout << "Flying to waypoint: (" << waypoint.x << ", " << waypoint.y << ", " << waypoint.altitude << ")" << std::endl;
}

void Drone::printStatus() const {
    std::cout << "Drone position: (" << x << ", " << y << ", " << altitude << ")" << std::endl;
    std::cout << "Battery level: " << batteryLevel << "%" << std::endl;
    std::cout << "Drone state: ";
    switch (state) {
        case DroneState::Grounded:
            std::cout << "Grounded" << std::endl;
            break;
        case DroneState::Armed:
            std::cout << "Armed" << std::endl;
            break;
        case DroneState::Flying:
            std::cout << "Flying" << std::endl;
            break;
    }
}