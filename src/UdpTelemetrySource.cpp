#include "UdpTelemetrySource.hpp"

#include <arpa/inet.h>
#include <cerrno>
#include <iostream>
#include <poll.h>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>

UdpTelemetrySource::UdpTelemetrySource(
    const std::string& bindAddress,
    std::uint16_t port
) 
    : running(false),
      bindAddress(bindAddress), 
      port(port) 
{
}

std::optional<VehicleState> UdpTelemetrySource::parseState(
    const std::string& state) const {
        if (state == "Grounded") {
            return VehicleState::Grounded;
        } 
        
        if (state == "Armed") {
            return VehicleState::Armed;
        }
        
        if (state == "Flying") {
            return VehicleState::Flying;
        } 
        
        return std::nullopt;
        
    }

std::optional<TelemetrySample> UdpTelemetrySource::parseSample(
    const std::string& message) const {
        std::stringstream lineStream(message);

        std::string elapsedTime;
        std::string x;
        std::string y;
        std::string altitude;
        std::string battery;
        std::string state;

        if (!std::getline(lineStream, elapsedTime, ',') ||
            !std::getline(lineStream, x, ',') ||
            !std::getline(lineStream, y, ',') ||
            !std::getline(lineStream, altitude, ',') ||
            !std::getline(lineStream, battery, ',') ||
            !std::getline(lineStream, state, ',')) {
            return std::nullopt;
        }

        while (!state.empty() &&
                (state.back() == '\n' || state.back() == '\r')) {
                state.pop_back();
        }

        std::optional<VehicleState> vehicleState = parseState(state);

        if (!vehicleState) {
            return std::nullopt;
        }

        try {
            return TelemetrySample{
                std::stod(elapsedTime),
                std::stod(x),
                std::stod(y),
                std::stod(altitude),
                std::stod(battery),
                vehicleState.value()
            };
        }

        catch (const std::exception&) {
            return std::nullopt;
        }
    }

void UdpTelemetrySource::run(
    std::stop_token stopToken) {
        int socketFd = socket(AF_INET, SOCK_DGRAM, 0);

        if (socketFd < 0) {
            std::cerr << "Failed to create socket.\n";
            running.store(false);
            return;
        }

        sockaddr_in address{};
        address.sin_family = AF_INET;
        address.sin_port = htons(port);

        if (inet_pton(
                AF_INET,
                bindAddress.c_str(),
                &address.sin_addr
            ) != 1) {
            std::cerr << "Invalid bind address.\n";
            close(socketFd);
            running.store(false);
            return;
        }

        if (bind(
                socketFd,
                reinterpret_cast<sockaddr*>(&address),
                sizeof(address)
        ) < 0) {
            std::cerr << "Failed to bind UDP socket.\n";
            close(socketFd);
            running.store(false);
            return;
        }

        std::cout
            << "Listening on "
            << bindAddress
            << ":"
            << port
            << "\n";

        while (!stopToken.stop_requested()) {
            pollfd descriptor{};
            descriptor.fd = socketFd;
            descriptor.events = POLLIN;

            int pollResult = poll(&descriptor, 1, 200);

            if (pollResult < 0) {
                if (errno == EINTR) {
                    continue;
                }

                std::cerr
                    << "UDP socket polling failed.\n";
                break;
            }

            if (pollResult == 0) {
                continue;
            }

            if (descriptor.revents & POLLIN) {
                char buffer[1024];

                ssize_t bytesReceived = recvfrom(
                    socketFd,
                    buffer,
                    sizeof(buffer),
                    0,
                    nullptr,
                    nullptr
                );

            if (bytesReceived < 0) {
                std::cerr
                    << "Failed to receive UDP data.\n";
                break;
            }

            std::string message(
                buffer,
                static_cast<size_t>(bytesReceived)
            );

            std::optional<TelemetrySample> sample = parseSample(message);

            if (sample) {
                publishSample(sample.value());
            } 
            else {
                std::cerr
                    << "Ignored malformed telemetry: "
                    << message
                    << "\n";
            }
        }
    }

    close(socketFd);
    running.store(false);
}