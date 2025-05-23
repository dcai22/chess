#pragma once

#include "piece.h"

class Pawn : public Piece {
 private:
    auto getDirection() const -> int;

 public:
    Pawn(const PieceColour colour);

    auto getStartingRow() const -> int override;
    auto getAttackedSquares(const Board& board, const Square& square) const -> std::vector<Square> override;
    auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> override;
};
