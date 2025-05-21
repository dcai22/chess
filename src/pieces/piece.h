#pragma once

#include "../types.h"

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

    virtual ~Piece() = default;
};
