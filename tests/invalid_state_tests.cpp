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

    if (replay.load(csvFilename)) {
        std::cerr << "Loaded invalid file: " << csvFilename << "\n";
        return 1;
    }

    std::cout << "Invalid data rejected. Test successful.\n";
    return 0;
}