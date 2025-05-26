#include <string>
#include <stdexcept>

#include "piece.h"
#include "../move.h"
#include "../constants.h"

Piece::Piece(const double value, const char symbol, const PieceColour& colour, const int startingRow)
: value_(value)
, symbol_(symbol)
, colour_(colour)
, startingRow_(startingRow)
{}

auto Piece::getStartingRow(const PieceColour& colour) const noexcept -> int {
    return colour == PieceColour::White ? 0 : 7;
}

auto Piece::getValue() const noexcept -> double {
    return value_;
}

auto Piece::getSymbol() const noexcept -> char {
    return symbol_;
}

auto Piece::getDisplaySymbol() const noexcept -> char {
    if (colour_ == PieceColour::White) {
        return static_cast<char>(std::toupper(symbol_));
    } else {
        return static_cast<char>(std::tolower(symbol_));
    }
}

auto Piece::getColour() const noexcept -> PieceColour {
    return colour_;
}

auto Piece::getLastMoved() const noexcept -> int {
    return lastMoved_;
}

auto Piece::hasMoved() const noexcept ->  bool {
    return lastMoved_ > 0;
}

auto Piece::isKing() const noexcept ->  bool {
    return getSymbol() == Constants::KING_SYMBOL;
}

auto Piece::isQueen() const noexcept ->  bool {
    return getSymbol() == Constants::QUEEN_SYMBOL;
}

auto Piece::isRook() const noexcept ->  bool {
    return getSymbol() == Constants::ROOK_SYMBOL;
}

auto Piece::isBishop() const noexcept ->  bool {
    return getSymbol() == Constants::BISHOP_SYMBOL;
}

auto Piece::isKnight() const noexcept ->  bool {
    return getSymbol() == Constants::KNIGHT_SYMBOL;
}

auto Piece::isPawn() const noexcept ->  bool {
    return getSymbol() == Constants::PAWN_SYMBOL;
}

auto Piece::isColour(const PieceColour& colour) const noexcept -> bool {
    return getColour() == colour;
}

auto Piece::getStartingRow() const noexcept -> int {
    return startingRow_;
}

auto Piece::setLastMoved(const int& moveNum) noexcept -> void {
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
