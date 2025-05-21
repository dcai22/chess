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
    bool lastMoved_ = 0;

 protected:
    Piece(const double value, const char symbol, const PieceColour colour);

    public:
    auto getValue() const -> double;
    auto getSymbol() const -> char;
    auto getColour() const -> PieceColour;
    auto getLastMoved() const -> int;
    auto hasMoved() const -> bool;

    auto setLastMoved(const int& moveNum) -> void;

    virtual auto deduceMoveType(const Board& board, const Move& move) const -> MoveType = 0;

    virtual ~Piece() = default;
};
