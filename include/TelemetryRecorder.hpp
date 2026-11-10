#pragma once

#include "TelemetryRecord.hpp"

#include <fstream>
#include <string>

class TelemetryRecorder {
    private:
        std::ofstream outputFile;

        std::string stateToString(VehicleState state) const;

    public:
        explicit TelemetryRecorder(const std::string& filename);

        bool isOpen() const;
        void record(const TelemetryRecord& record);
};
