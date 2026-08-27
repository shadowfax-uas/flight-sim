#ifndef TELEMETRY_RECORDER_HPP
#define TELEMETRY_RECORDER_HPP

#include "TelemetryRecord.hpp"

#include <fstream>
#include <string>

class TelemetryRecorder {
    private:
        std::ofstream outputFile;
        std::size_t nextFrameNumber;

        std::string stateToString(DroneState state) const;

    public:
        explicit TelemetryRecorder(const std::string& filename);

        bool isOpen() const;
        void record(const Drone& drone);
};

#endif