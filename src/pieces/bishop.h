#pragma once

#include <array>

#include "piece.h"

class Bishop : public Piece {
 private:
    inline static const std::vector<std::array<int, 2>> directions_{{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

 public:
    Bishop(const PieceColour& colour);

    [[nodiscard]] auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> override;
};
