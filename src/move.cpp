#include "move.h"
#include "helper.h"

Move::Move(const Square from, const Square to)
: from(from)
, to(to)
{}

auto Move::fromStr(const std::string& command) -> std::optional<Move> {
    auto tokens = splitByWhitespace(command);
    if (tokens.size() != 2) {
        return std::nullopt;
    }

    try {
        auto from = Square::parseCoords(tokens[0]);
        auto to = Square::parseCoords(tokens[1]);

        return Move(from, to);
    } catch (const std::exception&) {
        return std::nullopt;
    }
}

auto Move::operator==(const Move& other) const noexcept -> bool {
    return from == other.from && to == other.to;
}
