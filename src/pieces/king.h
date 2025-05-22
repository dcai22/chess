#pragma once

#include "piece.h"

class King : public Piece {
 private:
    auto getStartingRow() const -> int;

 public:
    King(const PieceColour colour);

    // auto deduceMoveType(const Board& board, const Move& move) const -> MoveType override;
    auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> override;
};
