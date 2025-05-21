#pragma once

#include "../types.h"

// forward declarations
class Board;
class Move;

class Piece {
 private:
    double value_;
    char symbol_;
    PieceColour colour_;

 protected:
    Piece(const double value, const char symbol, const PieceColour colour);

    public:
    auto getValue() const -> double;
    auto getSymbol() const -> char;
    auto getColour() const -> PieceColour;

    virtual auto canDoMove(const Board& board, const Move& move) const -> bool = 0;

    virtual ~Piece() = default;
};
