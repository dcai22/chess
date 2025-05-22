#pragma once

#include <string>
#include <vector>

#include "types.h"

auto splitByWhitespace(const std::string& str) -> std::vector<std::string>;
auto oppositeColour(const PieceColour& colour) -> PieceColour;
