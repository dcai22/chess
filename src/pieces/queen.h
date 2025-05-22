#pragma once

#include "piece.h"

class Queen : public Piece {
 public:
    Queen(const PieceColour colour);

    auto isAttack(const Board& board, const Move& move) const -> bool override;
    auto deduceMoveType(const Board& board, const Move& move) const -> MoveType override;
};
