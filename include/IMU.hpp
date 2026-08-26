#ifndef IMU_HPP
#define IMU_HPP

#include "Sensor.hpp"

class IMU : public Sensor {
    private:
        double altitude;
    public:
        IMU();
        
        void update(const Drone& drone) override;
        void printReading() const override;
};

#endif