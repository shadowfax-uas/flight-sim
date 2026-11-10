#include "TelemetryStatistics.hpp"

#include <vector>

const std::vector<TelemetryRecord> records = {
    {0, 2.0, 0.0, 0.0, 10, 100.0, VehicleState::Flying},
    {1, 3.0, 3.0, 4.0, 12, 100.0, VehicleState::Flying},
    {2, 5.5, 7.0, 4.0, 15, 99.5, VehicleState::Flying}
};

int main() {
    double duration = calculateDurationSeconds(records);
    if (duration != 3.5) {
        return 1; // Test failed
    }
    double distance = calculateDistanceTraveled(records);
    if (distance != 9.0) {
        return 1; // Test failed
    }

    std::vector<TelemetryRecord> emptyRecords;
    if (calculateDurationSeconds(emptyRecords) != 0.0) {
        return 1; // Test failed
    }
    if (calculateDistanceTraveled(emptyRecords) != 0.0) {
        return 1; // Test failed
    }

    std::vector<TelemetryRecord> singleRecord = {
        {0, 2.0, 5.0, 8.0, 10.0, 100.0, VehicleState::Flying}
    };
    if (calculateDurationSeconds(singleRecord) != 0.0) {
        return 1; // Test failed
    }
    if (calculateDistanceTraveled(singleRecord) != 0.0) {
        return 1; // Test failed
    }
    return 0; // Test passed
    
}