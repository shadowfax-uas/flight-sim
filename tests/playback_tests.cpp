#include <vector>
#include <iostream>

#include "TelemetryRecord.hpp"
#include "TelemetryPlayback.hpp"

const std::vector<TelemetryRecord> emptyRecords = {};

const std::vector<TelemetryRecord> testRecords = {
    {0, 0.0, 0.0, 0.0, 10, 100.0, VehicleState::Flying},
    {1, 0.01, 1.0, 1.0, 20, 99.5, VehicleState::Flying},
    {2, 0.02, 2.0, 2.0, 15, 99.0, VehicleState::Flying}
};

int callbackCount = 0;

int main() {
    // Test with empty records
    playTelemetry(emptyRecords, 1.0, [&](const TelemetryRecord& record) {
        ++callbackCount;
    });

    if (callbackCount != 0) {
        std::cerr << "Callback was called for empty input\n";
        return 1;
    }

    std::vector<std::size_t> receivedFrames;

    // Test with valid records
    playTelemetry(testRecords, 1.0, [&](const TelemetryRecord& record) {
        receivedFrames.push_back(record.frameNumber);
    });
    if (receivedFrames == std::vector<std::size_t>{0, 1, 2}) {
        std::cout << "Test passed: Received all records in order\n";
    } else {
        std::cerr << "Test failed: Did not receive all records in order\n";
        return 1;
    }
    return 0;
}