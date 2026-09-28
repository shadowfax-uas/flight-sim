#include "MockTelemetrySource.hpp"

#include <chrono>
#include <thread>
#include <vector>

MockTelemetrySource::MockTelemetrySource() : running(false) {}

void MockTelemetrySource::run(
    std::stop_token stopToken
) {
    std::vector<TelemetrySample> samples = {
        {0.0,  0.0,  0.0,  0.0, 100.0, VehicleState::Grounded},
        {0.5,  0.0,  0.0,  0.0, 100.0, VehicleState::Armed},
        {1.0,  0.0,  0.0, 10.0, 100.0, VehicleState::Flying},
        {1.5,  5.0, 10.0, 15.0,  99.5, VehicleState::Flying},
        {2.0, 10.0, 20.0, 20.0,  99.0, VehicleState::Flying},
        {2.5, 15.0, 30.0, 25.0,  98.5, VehicleState::Flying},
        {3.0, 15.0, 30.0,  0.0,  98.5, VehicleState::Grounded}
    };

    for (std::size_t i=0; i < samples.size(); ++i) {
        if (stopToken.stop_requested()) {
            break;
        }

        publishSample(samples[i]);

        if (i + 1 < samples.size()) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(500)
            );
        }
    }

    running.store(false);
};