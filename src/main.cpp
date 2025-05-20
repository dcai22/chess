#include <iostream>

#include "Board.h"

auto main() -> int {
    std::cout << "Welcome to Chess!" << std::endl;
    auto board = Board();
    board.printState();
    return 0;
}
