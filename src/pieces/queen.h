#pragma once

#include "piece.h"

class Queen : public Piece {
 public:
    Queen(const PieceColour colour);

    auto canDoMove(const Board& board, const Move& move) const -> bool override;
};
