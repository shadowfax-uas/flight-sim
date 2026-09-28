#ifndef MOCK_TELEMETRY_SOURCE_HPP
#define MOCK_TELEMETRY_SOURCE_HPP

#include "TelemetrySource.hpp"

#include <atomic>
#include <thread>

class MockTelemetrySource : public TelemetrySource {
    private:
        std::atomic<bool> running;
        std::jthread workerThread;

        void run(std::stop_token stopToken);

    public:
        MockTelemetrySource();

        void start();
        void stop();
        void wait();

        bool isRunning() const;
};

#endif