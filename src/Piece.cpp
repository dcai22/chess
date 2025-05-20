#include "Piece.h"

Piece::Piece(double value, char symbol)
: value(value)
, symbol(symbol)
{}

auto Piece::getValue() -> double {
    return this->value;
}

auto Piece::getSymbol() -> char {
    return this->symbol;
}
