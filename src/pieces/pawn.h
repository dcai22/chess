#pragma once

#include "piece.h"

class Pawn : public Piece {
 private:
    auto getDirection() const -> int;

 public:
    Pawn(const PieceColour colour);

    auto isAttack(const Board& board, const Move& move) const -> bool override;
    auto deduceMoveType(const Board& board, const Move& move) const -> MoveType override;
};
