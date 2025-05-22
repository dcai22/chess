#pragma once

#include "piece.h"

class Bishop : public Piece {
 public:
    Bishop(const PieceColour colour);

    auto isAttack(const Board& board, const Move& move) const -> bool override;
    auto deduceMoveType(const Board& board, const Move& move) const -> MoveType override;
};
