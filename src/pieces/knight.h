#pragma once

#include "piece.h"

class Knight : public Piece {
 public:
    Knight(const PieceColour colour);

    auto deduceMoveType(const Board& board, const Move& move) const -> MoveType override;
};
