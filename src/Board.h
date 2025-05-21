#ifndef BOARD_H
#define BOARD_H

#include <algorithm>
#include <vector>
#include <memory>

#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

class Board {
 private:
    std::unique_ptr<Piece> board_[8][8]; // e.g. e2 corresponds to board_[3][1] because 'e' -> 3 and '2' -> 1

 public:
    Board();

    auto printState() const -> void;
};

#endif // BOARD_H
