#include <iostream>

#include "Board.h"

Board::Board() {
    for (auto col = 0; col < 8; col++) {
        for (auto row = 0; row < 8; row++) {
            if (row == 1 || row == 6) {
                board_[row][col] = std::make_unique<Pawn>();
            } else if (row == 0 || row == 7) {
                if (col == 0 || col == 7) {
                    board_[row][col] = std::make_unique<Rook>();
                } else if (col == 1 || col == 6) {
                    board_[row][col] = std::make_unique<Knight>();
                } else if (col == 2 || col == 5) {
                    board_[row][col] = std::make_unique<Bishop>();
                } else if (col == 3) {
                    board_[row][col] = std::make_unique<Queen>();
                } else if (col == 4) {
                    board_[row][col] = std::make_unique<King>();
                }
            } else {
                board_[row][col] = nullptr;
            }
        }
    }
}

auto Board::printState() -> void {
    for (auto row = 7; row >= 0; row--) {
        for (auto col = 0; col < 8; col++) {
            std::cout << (this->board_[row][col] == nullptr ? '.' : this->board_[row][col]->getSymbol()) << " ";
        }
        std::cout << std::endl;
    }
}
