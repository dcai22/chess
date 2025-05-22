#pragma once

#include "piece.h"

class Rook : public Piece {
 public:
    Rook(const PieceColour colour);

    auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> override;
};
