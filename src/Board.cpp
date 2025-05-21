#include <iostream>

#include "Board.h"

Board::Board() {
    for (auto col = 0; col < 8; col++) {
        for (auto row = 0; row < 8; row++) {
            if (row == 0 || row == 7) {
                // pieces
                auto colour = row == 0 ? PieceColour::White : PieceColour::Black;
                if (col == 0 || col == 7) {
                    // rooks
                    board_[row][col] = std::make_unique<Rook>(colour);
                } else if (col == 1 || col == 6) {
                    // knights
                    board_[row][col] = std::make_unique<Knight>(colour);
                } else if (col == 2 || col == 5) {
                    // bishops
                    board_[row][col] = std::make_unique<Bishop>(colour);
                } else if (col == 3) {
                    // queen
                    board_[row][col] = std::make_unique<Queen>(colour);
                } else if (col == 4) {
                    // king
                    board_[row][col] = std::make_unique<King>(colour);
                }
            } else if (row == 1 || row == 6) {
                auto colour = row == 1 ? PieceColour::White : PieceColour::Black;
                // pawns
                board_[row][col] = std::make_unique<Pawn>(colour);
            }
        }
    }
}

auto Board::printState() const -> void {
    for (auto row = 7; row >= 0; row--) {
        for (auto col = 0; col < 8; col++) {
            std::cout << (this->board_[row][col] == nullptr ? '.' : this->board_[row][col]->getSymbol()) << " ";
        }
        std::cout << std::endl;
    }
}
