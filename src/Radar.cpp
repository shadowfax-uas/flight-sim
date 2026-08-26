#include "Radar.hpp"
#include <iostream>

Radar::Radar() : detectedRange(0.0) {}

void Radar::update(const Drone& drone) {
    detectedRange = drone.getAltitude();
}

void Radar::printReading() const {
    std::cout << "Radar Reading:\n";
    std::cout << "  Detected Range: " << detectedRange << "\n";
}