#ifndef MOCK_TELEMETRY_SOURCE_HPP
#define MOCK_TELEMETRY_SOURCE_HPP

#include "TelemetrySource.hpp"

class MockTelemetrySource : public TelemetrySource {
    private:
        std::jthread workerThread;
        std::atomic<bool> running;

        void run(std::stop_token stopToken);

    public:
        MockTelemetrySource();

        void start();
        void stop();
        void wait();

        bool isRunning() const;
};

#endif