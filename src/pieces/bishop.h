#pragma once

#include "piece.h"

class Bishop : public Piece {
 private:
    inline static const std::vector<std::vector<int>> directions_{{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

 public:
    Bishop(const PieceColour colour);

    [[nodiscard]] auto getStartingRow() const -> int override;
    [[nodiscard]] auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> override;
};
