#pragma once

#include "piece.h"

class Queen : public Piece {
 public:
    Queen(const PieceColour colour);

    auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> override;
};
