#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "Drone.hpp"

class Sensor {
    public:
        virtual void update(const Drone& drone) = 0;
        virtual void printReading() const = 0;

        virtual ~Sensor() = default;
};

#endif