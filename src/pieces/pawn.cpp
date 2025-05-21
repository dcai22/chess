#include "pawn.h"
#include "../constants.h"

Pawn::Pawn(const PieceColour colour)
: Piece(Constants::PAWN_SYMBOL, Constants::PAWN_SYMBOL, colour)
{}
