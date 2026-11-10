#pragma once

#include <optional>
#include <string>
#include <cmath>
#include <stdexcept>

namespace parsing {
    // Validate that the entire string can be converted to a double
    std::optional<double> parseStrictDouble(
        const std::string& text
    );
}