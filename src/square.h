#pragma once

class Square {
 public:
    int row;
    int col;

    Square(int row, int col);

    static auto isValid(const int row, const int col) -> bool;

    auto operator==(const Square& other) const -> bool;
    auto operator!=(const Square& other) const -> bool;
};
