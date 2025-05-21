#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "../types.h"

class Pawn : public Piece {
 public:
    Pawn(PieceColour colour);
};

#endif // PAWN_H
