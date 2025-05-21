#include <iostream>

#include "game.h"
#include "types.h"

auto main() -> int {
    std::cout << "Welcome to Chess!" << std::endl;
    auto game = Game();
    game.printBoard();

    while (!game.getHasEnded()) {
        std::cout << std::endl;
        switch (game.getColourToMove()) {
            case PieceColour::White:
            std::cout << "White to move!" << std::endl;
            break;
            
            case PieceColour::Black:
            std::cout << "Black to move!" << std::endl;
            break;
            
            default:
            break;
        }
        
        auto move = std::string();
        std::getline(std::cin >> std::ws, move);
        while (!Game::isValidMove(move)) {
            std::cout << "Please enter a valid move, e.g. e2 e4" << std::endl;
            std::getline(std::cin >> std::ws, move);
        }

        game.processMove(move);
        game.printBoard();
    }

    std::cout << "Game ended!" << std::endl;
    if (game.getWinner().has_value()) {
        switch(game.getWinner().value()) {
            case PieceColour::White:
                std::cout << "Winner: White!" << std::endl;
                break;
            
            case PieceColour::Black:
                std::cout << "Winner: Black!" << std::endl;
                break;

            default:
                break;
        }
    } else {
        std::cout << "Draw!" << std::endl;;
    }

    return 0;
}
