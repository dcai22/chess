#pragma once

#include <array>

#include "piece.h"

class Knight : public Piece {
 private:
    inline static const std::vector<std::array<int, 2>> directions_{{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

 public:
    Knight(const PieceColour& colour);

    [[nodiscard]] auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> override;
};
