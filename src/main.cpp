#include <iostream>

#include "game.h"
#include "types.h"
#include "move.h"

auto main() -> int {
    std::cout << "Welcome to Chess!" << std::endl;
    auto game = Game();
    game.printBoard();

    while (!game.hasEnded()) {
        std::cout << std::endl;
        switch (game.getColourToMove()) {
            case PieceColour::White:
                std::cout << "White to move!" << std::endl;
                break;

            case PieceColour::Black:
                std::cout << "Black to move!" << std::endl;
                break;
        }

        auto moveOpt = std::optional<Move>();
        while (true) {
            std::cout << "Enter move: ";
            auto command = std::string();
            std::getline(std::cin >> std::ws, command);
            moveOpt = Move::fromStr(command);

            if (moveOpt.has_value()) {
                break;
            } else {
                std::cout << "Invalid move" << std::endl;
            }
        }

        const auto move = moveOpt.value();
        game.processMove(move);
        game.printBoard();
    }

    std::cout << "Game over!" << std::endl;
    std::cout << "Result: ";
    if (game.getWinner().has_value()) {
        switch(game.getWinner().value()) {
            case PieceColour::White:
                std::cout << "White wins" << std::endl;
                break;

            case PieceColour::Black:
                std::cout << "Black wins" << std::endl;
                break;
        }
    } else {
        std::cout << "Draw" << std::endl;;
    }

    return 0;
}
