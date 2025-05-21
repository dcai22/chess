#pragma once

#include "piece.h"

class King : public Piece {
 public:
    King(const PieceColour colour);

    auto canDoMove(const Board& board, const Move& move) const -> bool override;
};
