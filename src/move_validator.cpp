#include <iostream>
#include <optional>

#include "move_validator.h"
#include "board.h"
#include "move.h"

auto MoveValidator::isValidMove(const Board& board, const Move& move, const PieceColour playerColour) -> bool {
    auto movingPiece = board.pieceAt(move.from).lock();

    if (!movingPiece) {
        std::cout << "There is no piece there!" << std::endl;
        return false;
    }

    if (movingPiece->getColour() != playerColour) {
        std::cout << "That piece does not belong to you!" << std::endl;
        return false;
    }
    
    if (move.from == move.to) {
        std::cout << "Start and end square cannot be the same" << std::endl;
        return false;
    }

    if (!movingPiece->canDoMove(board, move)) {
        std::cout << "That piece cannot move there!" << std::endl;
        return false;
    }

    // auto target = board.pieceAt(move.to).lock();

    return true;
}
