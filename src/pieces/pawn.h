#pragma once

#include "piece.h"

class Pawn : public Piece {
 private:
    const int direction_;

 protected:
    [[nodiscard]] auto getStartingRow(const PieceColour& colour) const noexcept -> int override;

 public:
    Pawn(const PieceColour& colour);

    [[nodiscard]] auto getAttackedSquares(const Board& board, const Square& square) const -> std::vector<Square> override;
    [[nodiscard]] auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> override;
};
