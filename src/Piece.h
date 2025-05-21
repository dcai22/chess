#ifndef PIECE_H
#define PIECE_H

#include "Types.h"

class Piece {
 private:
    double value;
    char symbol;
    PieceColour colour;

 protected:
    Piece(double value, char symbol, PieceColour colour);
    
    public:
    auto getValue() const -> double;
    auto getSymbol() const -> char;

    virtual ~Piece() = default;
};

#endif // PIECE_H
