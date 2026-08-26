#include "SensorManager.hpp"

#include <utility>

void SensorManager::addSensor(std::unique_ptr<Sensor> sensor) {
    sensors.push_back(std::move(sensor));
}

void SensorManager::updateAll(const Drone& drone) {
    for (const auto& sensor : sensors) {
        sensor->update(drone);
    }
}

void SensorManager::printAll() const {
    for (const auto& sensor : sensors) {
        sensor->printReading();
    }
}