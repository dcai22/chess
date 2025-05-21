#pragma once

#include "piece.h"

class Rook : public Piece {
 public:
    Rook(const PieceColour colour);

    auto canDoMove(const Board& board, const Move& move) const -> bool override;
};
