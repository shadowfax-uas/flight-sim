#ifndef GPS_HPP
#define GPS_HPP

#include "Drone.hpp"
#include "Sensor.hpp"

class GPS : public Sensor {
    private:
        double x;
        double y;
        double altitude;

    public:
    GPS();
    
    void update(const Drone& drone) override;
    void printReading() const override;
};

#endif