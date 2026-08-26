#ifndef RADAR_HPP
#define RADAR_HPP

#include "Sensor.hpp"

class Radar : public Sensor {
    private:
        double detectedRange;
    public:
        Radar();
        
        void update(const Drone& drone) override;
        void printReading() const override;
};

#endif