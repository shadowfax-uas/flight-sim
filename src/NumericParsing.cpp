#include "NumericParsing.hpp"

namespace parsing {
    // Validate that the entire string can be converted to a double
    std::optional<double> parseStrictDouble(
        const std::string& text
    ) { try {
            std::size_t characterConsumed = 0;
            double value = std::stod(text, &characterConsumed);
            if (characterConsumed != text.size()) {
                return std::nullopt;
            }
            if (!std::isfinite(value)) {
                return std::nullopt;
            }
            return value;
    }
    catch (const std::invalid_argument& error) {
        return std::nullopt;
    }
    catch (const std::out_of_range& error) {
        return std::nullopt;
    }
    }
}