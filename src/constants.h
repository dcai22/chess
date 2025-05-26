#pragma once

#include <math.h>

namespace Constants {
    constexpr int BOARD_SIZE = 8;

    // piece values
    constexpr double PAWN_VALUE = 1;
    constexpr double ROOK_VALUE = 5;
    constexpr double KNIGHT_VALUE = 3;
    constexpr double BISHOP_VALUE = 3;
    constexpr double QUEEN_VALUE = 9;
    constexpr double KING_VALUE = INFINITY;

    // piece symbols
    constexpr char PAWN_SYMBOL = 'P';
    constexpr char ROOK_SYMBOL = 'R';
    constexpr char KNIGHT_SYMBOL = 'N';
    constexpr char BISHOP_SYMBOL = 'B';
    constexpr char QUEEN_SYMBOL = 'Q';
    constexpr char KING_SYMBOL = 'K';

    constexpr int REPEATED_POSITION_LIMIT = 3;
}
