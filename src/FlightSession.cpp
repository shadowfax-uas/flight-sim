#include "FlightSession.hpp"

FlightSession::FlightSession(
    const std::string& sessionId,
    const std::string& vehicleId,
    FlightSource source,
    std::time_t startTime
) 
    : sessionId(sessionId), 
      vehicleId(vehicleId), 
      source(source), 
      startTime(startTime),
      endTime(std::nullopt) {

      }

const std::string& FlightSession::getSessionId() const {
    return sessionId;
}

const std::string& FlightSession::getVehicleId() const {
    return vehicleId;
}

FlightSource FlightSession::getSource() const {
    return source;
}

std::time_t FlightSession::getStartTime() const {
    return startTime;
}

const std::optional<std::time_t>& 
FlightSession::getEndTime() const {
    return endTime;
}

bool FlightSession::isComplete() const {
    return endTime.has_value();
}

void FlightSession::endSession(std::time_t endTime) {
    this->endTime = endTime;
}

void FlightSession::addTelemetryRecord(const TelemetryRecord& record) {
    telemetryRecords.push_back(record);
}

const std::vector<TelemetryRecord>& FlightSession::getTelemetryRecords() const {
    return telemetryRecords;
}

void FlightSession::addRawLogFile(const std::string& filename) {
    rawLogFiles.push_back(filename);
}

const std::vector<std::string>& FlightSession::getRawLogFiles() const {
    return rawLogFiles;
}

