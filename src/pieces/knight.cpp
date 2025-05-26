#include "knight.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

Knight::Knight(const PieceColour colour)
: Piece(Constants::KNIGHT_SYMBOL, Constants::KNIGHT_SYMBOL, colour)
{}

auto Knight::getStartingRow() const -> int {
    return getColour() == PieceColour::White ? 0 : 7;
}

auto Knight::getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> {
    auto legalMoves = std::vector<LegalMove>();
    for (const auto& direction : directions_) {
        const auto toRow = from.row + direction[0];
        const auto toCol = from.col + direction[1];
        if (!Square::isValid(toRow, toCol)) {
            continue;
        }

        const auto to = Square(toRow, toCol);
        const auto toPiece = board.pieceAt(to).lock();
        if (toPiece) {
            if (!toPiece->isColour(getColour())) {
                const auto move = Move(from, to);
                legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::Capture });
            }
        } else {
            const auto move = Move(from, to);
            legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::Move });
        }
    }

    return legalMoves;
}
