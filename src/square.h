#pragma once

#include <string>

class Square {
 public:
    int row;
    int col;

    Square(const int row, const int col);

    [[nodiscard]] auto toString() const -> std::string;

    [[nodiscard]] static auto parseCoords(const std::string& coords) -> Square;
    [[nodiscard]] static auto isValid(const int row, const int col) noexcept -> bool;

    [[nodiscard]] auto operator==(const Square& other) const noexcept -> bool;
};
