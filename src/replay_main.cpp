#include "TelemetryReplay.hpp"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: flight-replay <telemetry_file>\n";
        return 1;
    }

    std::string filename = argv[1];

    TelemetryReplay replay;

    if (!replay.load(filename)) {
        std::cerr << "Failed to load telemetry file: " << filename << "\n";
        return 1;
    }

    std::cout << "Loaded " << replay.getRecordCount() << " telemetry records.\n";

    const TelemetryRecord& record = replay.current();
    std::cout << "Frame " << record.frameNumber
              << ": "
              << record.x << ", "
              << record.y << ", "
              << record.altitude << "\n";

    while (replay.next()) {
        const TelemetryRecord& record = replay.current();
        std::cout << "Frame " << record.frameNumber
                  << ": "
                  << record.x << ", "
                  << record.y << ", "
                  << record.altitude << "\n";
    }
}
