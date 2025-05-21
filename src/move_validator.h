#pragma once

#include "board.h"
#include "move.h"
#include "types.h"

class MoveValidator {
 public:
    auto isValidMove(const Board& board, const Move& move, const PieceColour playerColour) -> bool;
};
