#pragma once

#include "piece.h"

class Queen : public Piece {
 public:
    Queen(const PieceColour colour);

    auto deduceMoveType(const Board& board, const Move& move) const -> MoveType override;
};
