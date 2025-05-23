#pragma once

#include "piece.h"

class King : public Piece {
 public:
    King(const PieceColour colour);

    auto getStartingRow() const -> int override;
    auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> override;
};
