#ifndef SIMULATED_DRONE_SOURCE_HPP
#define SIMULATED_DRONE_SOURCE_HPP

#include "Drone.hpp"
#include "TelemetrySource.hpp"

class SimulatedDroneSource : public TelemetrySource {
    private:
        const Drone& drone;

    public:
        explicit SimulatedDroneSource(const Drone& drone);

        TelemetrySample sample() const override;

    
};

#endif