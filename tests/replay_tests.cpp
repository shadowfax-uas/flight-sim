/*
Goals for main():

1. Accepts the CSV filename as a command-line argument.

2. Constructs TelemetryReplay and calls load().

3. Verifies that exactly three records were loaded.

4. Checks that the first record has frame number 0.

5. Calls seek(2) and checks that the third record has x == 3.0.

6. Returns 0 on success and 1 on failure, printing a useful failure message.
*/

#include <iostream>
#include <string>

#include "TelemetryReplay.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <csv_filename>\n";
        return 1;
    }

    std::string csvFilename = argv[1];
    TelemetryReplay replay;

    if (!replay.load(csvFilename)) {
        std::cerr << "Failed to load CSV file: " << csvFilename << "\n";
        return 1;
    }

    if (replay.getRecordCount() != 3) {
        std::cerr << "Expected 3 records, but got " << replay.getRecordCount() << "\n";
        return 1;
    }

    if (!replay.seek(0)) {
        std::cerr << "Failed to seek to the first record.\n";
        return 1;
    }
    const auto& firstRecord = replay.current();
    if (firstRecord.frameNumber != 0) {
        std::cerr << "Expected first record frame number to be 0, but got "
                  << firstRecord.frameNumber << "\n";
        return 1;
    }

    if (!replay.seek(2)) {
        std::cerr << "Failed to seek to the third record.\n";
        return 1;
    }
    
    const auto& thirdRecord = replay.current();
    if (thirdRecord.x != 3.0) {
        std::cerr << "Expected third record x to be 3.0, but got "
                  << thirdRecord.x << "\n";
        return 1;
    }

    std::cout << "All tests passed successfully.\n";
    return 0;
}