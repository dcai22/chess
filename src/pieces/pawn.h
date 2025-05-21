#pragma once

#include "piece.h"

class Pawn : public Piece {
 public:
    Pawn(const PieceColour colour);

    auto deduceMoveType(const Board& board, const Move& move) const -> MoveType override;
};
