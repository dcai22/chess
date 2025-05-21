#pragma once

#include "piece.h"

class Pawn : public Piece {
 public:
    Pawn(const PieceColour colour);

    auto canDoMove(const Board& board, const Move& move) const -> bool override;
};
