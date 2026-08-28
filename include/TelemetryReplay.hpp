#ifndef TELEMETRY_REPLAY_HPP
#define TELEMETRY_REPLAY_HPP

#include "TelemetryRecord.hpp"

#include <cstddef>
#include <string>
#include <vector>

class TelemetryReplay {
    private:
        std::vector<TelemetryRecord> records;
        std::size_t currentIndex;

        DroneState stateFromString(const std::string& state) const;
    public:
        TelemetryReplay();

        bool load(const std::string& filename);

        bool hasRecords() const;
        std::size_t getRecordCount() const;

        const TelemetryRecord& current() const;

        bool next();
        bool previous();
        bool seek(std::size_t index);


};

#endif