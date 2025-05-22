#include <string>
#include <stdexcept>

#include "piece.h"
#include "../move.h"
#include "../constants.h"

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

auto Piece::isKing() const ->  bool {
    return getSymbol() == Constants::KING_SYMBOL;
}

auto Piece::isQueen() const ->  bool {
    return getSymbol() == Constants::QUEEN_SYMBOL;
}

auto Piece::isRook() const ->  bool {
    return getSymbol() == Constants::ROOK_SYMBOL;
}

auto Piece::isBishop() const ->  bool {
    return getSymbol() == Constants::BISHOP_SYMBOL;
}

auto Piece::isKnight() const ->  bool {
    return getSymbol() == Constants::KNIGHT_SYMBOL;
}

auto Piece::isPawn() const ->  bool {
    return getSymbol() == Constants::PAWN_SYMBOL;
}

auto Piece::isColour(const PieceColour& colour) const -> bool {
    return getColour() == colour;
}

auto Piece::setLastMoved(const int& moveNum) -> void {
    lastMoved_ = moveNum;
}

auto Piece::getAttackedSquares(const Board& board, const Square& from) const -> std::vector<Square> {
    auto attackedSquares = std::vector<Square>();
    for (const auto& legalMove : getLegalMoves(board, from)) {
        attackedSquares.push_back(legalMove.move.to);
    }
    return attackedSquares;
}

auto Piece::isAttack(const Board& board, const Move& move) const -> bool {
    for (const auto& attackedSquare : getAttackedSquares(board, move.from)) {
        if (attackedSquare == move.to) {
            return true;
        }
    }
    return false;
}
