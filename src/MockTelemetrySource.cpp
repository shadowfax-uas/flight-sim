#include "MockTelemetrySource.hpp"

#include <chrono>
#include <thread>
#include <vector>

void MockTelemetrySource::run() const {
    std::vector<TelemetrySample> samples = {
        {0.0,  0.0,  0.0,  0.0, 100.0, VehicleState::Grounded},
        {0.5,  0.0,  0.0,  0.0, 100.0, VehicleState::Armed},
        {1.0,  0.0,  0.0, 10.0, 100.0, VehicleState::Flying},
        {1.5,  5.0, 10.0, 15.0,  99.5, VehicleState::Flying},
        {2.0, 10.0, 20.0, 20.0,  99.0, VehicleState::Flying},
        {2.5, 15.0, 30.0, 25.0,  98.5, VehicleState::Flying},
        {3.0, 15.0, 30.0,  0.0,  98.5, VehicleState::Grounded}
    };

    for (const TelemetrySample& sample : samples) {
        publishSample(sample);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
};