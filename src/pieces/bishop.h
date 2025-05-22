#pragma once

#include "piece.h"

class Bishop : public Piece {
 public:
    Bishop(const PieceColour colour);

    auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> override;
};
