#pragma once

#include <array>

#include "piece.h"

class Rook : public Piece {
 private:
    inline static const std::vector<std::array<int, 2>> directions_{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

 public:
    Rook(const PieceColour& colour);

    [[nodiscard]] auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> override;
};
