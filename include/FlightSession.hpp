#ifndef FLIGHT_SESSION_HPP
#define FLIGHT_SESSION_HPP

#include "TelemetryRecord.hpp"

#include <ctime>
#include <optional>
#include <string>
#include <vector>

enum class FlightSource {
    Simulator,
    LiveMavlink,
    ImportedLog
};

class FlightSession {
    private:
        std::string sessionId;
        std::string vehicleId;
        FlightSource source;

        std::time_t startTime;
        std::optional<std::time_t> endTime;

        std::vector<TelemetryRecord> telemetryRecords;
        std::vector<std::string> rawLogFiles;

    public:
        FlightSession(
            const std::string& sessionId,
            const std::string& vehicleId,
            FlightSource source,
            std::time_t startTime
        );

        const std::string& getSessionId() const;
        const std::string& getVehicleId() const;
        FlightSource getSource() const;

        std::time_t getStartTime() const;
        const std::optional<std::time_t>& getEndTime() const;

        bool isComplete() const;
        void endSession(std::time_t endTime);

        void addTelemetryRecord(const TelemetryRecord& record);
        const std::vector<TelemetryRecord>& getTelemetryRecords() const;

        void addRawLogFile(const std::string& filename);
        const std::vector<std::string>& getRawLogFiles() const;
};

#endif