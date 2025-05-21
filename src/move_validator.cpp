#include <iostream>

#include "move_validator.h"

auto MoveValidator::isValidMove(const Board& board, const Move& move) -> bool {
    if (board.hasEnded()) {
        std::cout << "Game already ended" << std::endl;
        return false;
    } else if (move.from == move.to) {
        std::cout << "Start and end square cannot be the same" << std::endl;
        return false;
    } else {
        return true;
    }
}
