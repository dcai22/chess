#include <sstream>

#include "helper.h"

auto splitByWhitespace(const std::string& str) -> std::vector<std::string> {
    auto tokens = std::vector<std::string>();
    auto token = std::string();
    auto iss = std::istringstream(str);
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

auto oppositeColour(const PieceColour& colour) noexcept -> PieceColour {
    return colour == PieceColour::White ? PieceColour::Black : PieceColour::White;
}
