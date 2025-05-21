#pragma once

#include "types.h"

// forward declarations
class Board;
class Move;

class MoveValidator {
 public:
    auto isValidMove(const Board& board, const Move& move, const PieceColour playerColour) -> bool;
};
