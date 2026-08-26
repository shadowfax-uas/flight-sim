#include "IMU.hpp"
#include <iostream>

IMU::IMU() : altitude(0.0) {}

void IMU::update(const Drone& drone) {
    altitude = drone.getAltitude();
}
void IMU::printReading() const {
    std::cout << "IMU Reading:\n";
    std::cout << "  Altitude: " << altitude << "\n";
}