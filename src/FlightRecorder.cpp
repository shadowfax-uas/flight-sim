#include "FlightRecorder.hpp"

FlightRecorder::FlightRecorder(
    const std::string& sessionId,
    const std::string& vehicleId,
    FlightSource source,
    std::time_t startTime,
    const std::string& telemetryFilename
)
    : session(sessionId, vehicleId, source, startTime),
      telemetryRecorder(telemetryFilename),
      nextFrameNumber(0)
      {
    // Constructor implementation
}

bool FlightRecorder::isOpen() const {
    return telemetryRecorder.isOpen();
}

void FlightRecorder::record(const Drone& drone) {
    TelemetryRecord record{
        nextFrameNumber,
        drone.getX(),
        drone.getY(),
        drone.getAltitude(),
        drone.getBatteryLevel(),
        drone.getState()
    };

    ++nextFrameNumber;
    session.addTelemetryRecord(record);
    telemetryRecorder.record(record);

}

void FlightRecorder::endSession(std::time_t endTime) {
    session.endSession(endTime);
}

const FlightSession& FlightRecorder::getSession() const {
        return session;
    }