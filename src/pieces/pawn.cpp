#include "pawn.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

Pawn::Pawn(const PieceColour colour)
: Piece(Constants::PAWN_SYMBOL, Constants::PAWN_SYMBOL, colour)
{}

auto Pawn::canDoMove(const Board& board, const Move& move) const -> bool {
    return true;
}
