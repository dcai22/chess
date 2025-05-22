#pragma once

#include <optional>
#include <string>

#include "square.h"
#include "types.h"

class Move {
 public:
    Square from;
    Square to;

    Move(const Square from, const Square to);

    static auto fromStr(const std::string& command) -> std::optional<Move>;

    auto operator==(const Move& other) const -> bool;
};

struct LegalMove {
    Move move;
    MoveType moveType;
};
