#include "bishop.h"
#include "constants.h"

Bishop::Bishop(PieceColour colour)
: Piece(Constants::BISHOP_VALUE, Constants::BISHOP_SYMBOL, colour)
{}