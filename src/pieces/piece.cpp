#include <string>
#include <stdexcept>

#include "piece.h"

Piece::Piece(const double value, const char symbol, const PieceColour colour)
: value_(value)
, symbol_(symbol)
, colour_(colour)
{}

auto Piece::getValue() const -> double {
    return value_;
}

auto Piece::getSymbol() const -> char {
    return symbol_;
}

auto Piece::getDisplaySymbol() const -> char {
    switch (colour_) {
        case PieceColour::White:
            return static_cast<char>(std::toupper(symbol_));

        case PieceColour::Black:
            return static_cast<char>(std::tolower(symbol_));

        default:
            throw std::logic_error("Piece does not have a colour");
    }
}

auto Piece::getColour() const -> PieceColour {
    return colour_;
}

auto Piece::getLastMoved() const -> int {
    return lastMoved_;
}

auto Piece::hasMoved() const ->  bool {
    return lastMoved_ > 0;
}

auto Piece::setLastMoved(const int& moveNum) -> void {
    lastMoved_ = moveNum;
}
