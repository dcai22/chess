#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "../types.h"

class Queen : public Piece {
 public:
    Queen(PieceColour colour);
};

#endif // QUEEN_H
