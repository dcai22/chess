#pragma once

#include "piece.h"

class King : public Piece {
 public:
    King(const PieceColour colour);

    auto deduceMoveType(const Board& board, const Move& move) const -> MoveType override;
};
