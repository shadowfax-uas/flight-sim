#ifndef MOCK_TELEMETRY_SOURCE_HPP
#define MOCK_TELEMETRY_SOURCE_HPP

#include "TelemetrySource.hpp"

class MockTelemetrySource : public TelemetrySource {
    public:
        void run() const;
};

#endif