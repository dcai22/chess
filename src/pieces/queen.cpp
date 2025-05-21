#include "queen.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

Queen::Queen(const PieceColour colour)
: Piece(Constants::QUEEN_SYMBOL, Constants::QUEEN_SYMBOL, colour)
{}

auto Queen::canDoMove(const Board& board, const Move& move) const -> bool {
    return true;
}
