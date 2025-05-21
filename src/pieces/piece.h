#pragma once

#include "../types.h"

class Piece {
 private:
    double value_;
    char symbol_;
    PieceColour colour_;

 protected:
    Piece(double value, char symbol, PieceColour colour);

    public:
    auto getValue() const -> double;
    auto getSymbol() const -> char;

    virtual ~Piece() = default;
};
