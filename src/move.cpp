#include "move.h"
#include "helper.h"

Move::Move(Square from, Square to)
: from(from)
, to(to)
{}

auto Move::fromStr(const std::string& command) -> std::optional<Move> {
    auto tokens = splitByWhitespace(command);
    if (tokens.size() != 2 || tokens[0].size() != 2 || tokens[1].size() != 2) {
        return std::nullopt;
    }

    auto fromCol = tokens[0][0] - 'a';
    auto fromRow = tokens[0][1] - '1';
    auto toCol = tokens[1][0] - 'a';
    auto toRow = tokens[1][1] - '1';

    try {
        auto from = Square(fromRow, fromCol);
        auto to = Square(toRow, toCol);

        return std::make_optional(Move(from, to));
    } catch (const std::exception& _) {
        return std::nullopt;
    }
}
