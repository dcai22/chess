#pragma once

#include <string>
#include <vector>

#include "types.h"

[[nodiscard]] auto splitByWhitespace(const std::string& str) -> std::vector<std::string>;
[[nodiscard]] auto oppositeColour(const PieceColour& colour) noexcept -> PieceColour;
