#pragma once

#include "piece.h"

class Queen : public Piece {
 private:
    inline static const std::vector<std::vector<int>> directions_{{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

 public:
    Queen(const PieceColour colour);

    [[nodiscard]] auto getStartingRow() const -> int override;
    [[nodiscard]] auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> override;
};
