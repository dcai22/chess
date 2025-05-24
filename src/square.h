#pragma once

#include <string>

class Square {
 public:
    int row;
    int col;

    Square(const int row, const int col);

    auto toString() const -> std::string;

    static auto parseCoords(const std::string& coords) -> Square;
    static auto isValid(const int row, const int col) -> bool;

    auto operator==(const Square& other) const -> bool;
};
