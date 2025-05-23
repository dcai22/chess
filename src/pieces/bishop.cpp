#include <set>
#include <vector>

#include "bishop.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"
#include "../square.h"

Bishop::Bishop(const PieceColour colour)
: Piece(Constants::BISHOP_VALUE, Constants::BISHOP_SYMBOL, colour)
{}

auto Bishop::getStartingRow() const -> int {
    return getColour() == PieceColour::White ? 0 : 7;
}

auto Bishop::getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> {
    auto legalMoves = std::vector<LegalMove>();
    const auto directions = std::vector<std::vector<int>>({{1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
    for (const auto& direction : directions) {
        auto toRow = from.row;
        auto toCol = from.col;
        while (true) {
            toRow += direction[0];
            toCol += direction[1];
            if (!Square::isValid(toRow, toCol)) {
                break;
            }

            const auto to = Square(toRow, toCol);
            const auto toPiece = board.pieceAt(to).lock();
            if (toPiece) {
                if (!toPiece->isColour(getColour())) {
                    const auto move = Move(from, to);
                    legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::Capture });
                }
                break;
            } else {
                const auto move = Move(from, to);
                legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::Move });
            }
        }
    }

    return legalMoves;
}
