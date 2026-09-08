#ifndef FLIGHT_RECORDER_HPP
#define FLIGHT_RECORDER_HPP

#include "Drone.hpp"
#include "FlightSession.hpp"
#include "TelemetryRecorder.hpp"

#include <cstddef>
#include <ctime>
#include <string>

class FlightRecorder {
    private:
        FlightSession session;
        TelemetryRecorder telemetryRecorder;
        std::size_t nextFrameNumber;

    public:
        FlightRecorder(
            const std::string& sessionId,
            const std::string& vehicleId,
            FlightSource source,
            std::time_t startTime,
            const std::string& telemetryFilename
        );

        bool isOpen() const;
        void record(const Drone& drone);
        void endSession(std::time_t endTime);

        const FlightSession& getSession() const;
};

#endif