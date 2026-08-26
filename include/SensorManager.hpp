#ifndef SENSOR_MANAGER_HPP
#define SENSOR_MANAGER_HPP

#include "Sensor.hpp"

#include <vector>
#include <memory>

class SensorManager {
    private:
        std::vector<std::unique_ptr<Sensor>> sensors;
    public:
        void addSensor(std::unique_ptr<Sensor> sensor);
        void updateAll(const Drone& drone);
        void printAll() const;
};

#endif