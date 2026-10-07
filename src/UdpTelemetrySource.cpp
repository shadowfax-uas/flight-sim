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