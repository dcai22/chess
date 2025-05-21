#include <stdexcept>

#include "square.h"
#include "constants.h"

Square::Square(const int row, const int col)
: row(row)
, col(col)
{
    if (!isValid(row, col)) {
        throw std::invalid_argument("Coordinates must refer to a square on the board");
    }
}

auto Square::parseCoords(const std::string& coords) -> Square {
    if (coords.size() != 2) {
        throw std::invalid_argument("Coordinates must be a letter followed by a digit");
    }

    const auto col = coords[0] - 'a';
    const auto row = coords[1] - '1';

    return Square(row, col);
}

auto Square::isValid(const int row, const int col) -> bool {
    if ((0 <= row && row < Constants::BOARD_SIZE) &&
        (0 <= col && col < Constants::BOARD_SIZE)) {
        return true;
    } else {
        return false;
    }
}

auto Square::operator==(const Square& other) const -> bool {
    return row == other.row && col == other.col;
}

auto Square::operator!=(const Square& other) const -> bool {
    return !(*this == other);
}
