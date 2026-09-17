#include "SimulatedDroneSource.hpp"

SimulatedDroneSource::SimulatedDroneSource(const Drone& drone) : drone(drone) {}

TelemetrySample SimulatedDroneSource::sample() const {
    return TelemetrySample{
        drone.getSimulationTimeSeconds(),
        drone.getX(),
        drone.getY(),
        drone.getAltitude(),
        drone.getBatteryLevel(),
        drone.getState()
    };
}