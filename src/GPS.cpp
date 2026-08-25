#include "GPS.hpp"
#include <iostream>

GPS::GPS() : x(0.0), y(0.0), altitude(0.0) {}

void GPS::update(const Drone& drone) {
    x = drone.getX();
    y = drone.getY();
    altitude = drone.getAltitude();
}

void GPS::printReading() const {
    std::cout << "GPS Reading:" << std::endl;
    std::cout << "  X: " << x << std::endl;
    std::cout << "  Y: " << y << std::endl;
    std::cout << "  Altitude: " << altitude << std::endl;
}