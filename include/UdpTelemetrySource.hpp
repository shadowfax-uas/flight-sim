#ifndef UDP_TELEMETRY_SOURCE_HPP
#define UDP_TELEMETRY_SOURCE_HPP

#include "TelemetrySource.hpp"

#include <atomic>
#include <cstdint>
#include <optional>
#include <string>
#include <thread>

class UdpTelemetrySource : public TelemetrySource {
    private:
        std::atomic<bool> running;
        std::jthread workerThread;

        std::string bindAddress;
        std::uint16_t port;

        void run(std::stop_token stopToken);

        std::optional<TelemetrySample> parseSample(
            const std::string& message
        ) const;

        std::optional<VehicleState> parseState(
            const std::string& state
        ) const;

    public:
        UdpTelemetrySource(
            const std::string& bindAddress,
            std::uint16_t port
        );

        void start();
        void stop();
        void wait();

        bool isRunning() const;
};

#endif