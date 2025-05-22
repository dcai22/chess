#pragma once

#include "piece.h"

class King : public Piece {
 private:
    auto getStartingRow() const -> int;

 public:
    King(const PieceColour colour);

    auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> override;
};
