#include "Drone.hpp"
#include <iostream>

Drone::Drone() : x(0), y(0), altitude(0), batteryLevel(100), state(DroneState::Grounded) {}

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
    x = waypoint.x;
    y = waypoint.y;
    altitude = waypoint.altitude;
    batteryLevel -= 5;
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