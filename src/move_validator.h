#pragma once

#include "board.h"
#include "move.h"

class MoveValidator {
 public:
    auto isValidMove(const Board& board, const Move& move) -> bool;
};
