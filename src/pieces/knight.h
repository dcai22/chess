#pragma once

#include "piece.h"

class Knight : public Piece {
 public:
    Knight(const PieceColour colour);

    auto canDoMove(const Board& board, const Move& move) const -> bool override;
};
