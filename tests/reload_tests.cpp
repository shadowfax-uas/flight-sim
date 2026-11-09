/*
Creates one TelemetryReplay instance.

Successfully loads tests/data/valid.csv.

Verifies it contains three records.

Attempts to load a nonexistent file.

Verifies that load() returns false.

Verifies hasRecords() is false and getRecordCount() is zero.
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
        std::cerr << "Failed to load " << csvFilename << "\n";
        return 1;
    }

    if (replay.getRecordCount() != 3) {
        std::cerr << "Expected 3 records, but got " << replay.getRecordCount() << "\n";
        return 1;
    }

    if (replay.load("tests/data/nonexistent_file.csv")) {
        std::cerr << "Expected load() to fail for nonexistent file, but it succeeded\n";
        return 1;
    }

    if (replay.hasRecords()) {
        std::cerr << "Expected hasRecords() to be false after failed load, but it is true\n";
        return 1;
    }

    if (replay.getRecordCount() != 0) {
        std::cerr << "Expected getRecordCount() to be 0 after failed load, but got "
                  << replay.getRecordCount() << "\n";
        return 1;
    }

    std::cout << "All tests passed successfully.\n";
    return 0;
}