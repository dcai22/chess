#pragma once

#include "piece.h"

class Bishop : public Piece {
 public:
    Bishop(const PieceColour colour);

    auto canDoMove(const Board& board, const Move& move) const -> bool override;
};
