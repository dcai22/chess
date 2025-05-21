#pragma once

#include <optional>
#include <string>

#include "square.h"

class Move {
 public:
    Square from;
    Square to;

    Move(const Square from, const Square to);

    static auto fromStr(const std::string& command) -> std::optional<Move>;
};
