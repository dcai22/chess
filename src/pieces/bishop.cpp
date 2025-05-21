#include "bishop.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

Bishop::Bishop(const PieceColour colour)
: Piece(Constants::BISHOP_VALUE, Constants::BISHOP_SYMBOL, colour)
{}

auto Bishop::canDoMove(const Board& board, const Move& move) const -> bool {
    return true;
}
