#include "rook.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

Rook::Rook(const PieceColour colour)
: Piece(Constants::ROOK_SYMBOL, Constants::ROOK_SYMBOL, colour)
{}

auto Rook::canDoMove(const Board& board, const Move& move) const -> bool {
    return true;
}
