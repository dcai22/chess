#include <string>

#include "piece.h"

Piece::Piece(double value, char symbol, PieceColour colour)
: value(value)
, symbol(symbol)
, colour(colour)
{}

auto Piece::getValue() const -> double {
    return this->value;
}

auto Piece::getSymbol() const -> char {
    auto rawSymbol = this->symbol;
    if (this->colour == PieceColour::White) {
        return static_cast<char>(std::toupper(rawSymbol));
    } else {
        return static_cast<char>(std::tolower(rawSymbol));
    }
}
