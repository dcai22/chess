#include "knight.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

Knight::Knight(const PieceColour colour)
: Piece(Constants::KNIGHT_SYMBOL, Constants::KNIGHT_SYMBOL, colour)
{}

auto Knight::canDoMove(const Board& board, const Move& move) const -> bool {
    return true;
}
