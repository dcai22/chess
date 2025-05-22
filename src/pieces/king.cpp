#include "king.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

King::King(const PieceColour colour)
: Piece(Constants::KING_VALUE, Constants::KING_SYMBOL, colour)
{}

auto King::getStartingRow() const -> int {
    return getColour() == PieceColour::White ? 0 : 7;
}

// TODO: castling logic
// auto King::deduceMoveType(const Board& board, const Move& move) const -> MoveType {
    // const auto fromRow = move.from.row;
    // const auto fromCol = move.from.col;

    // const auto directions = std::vector<std::vector<int>>({{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
    // for (const auto& direction : directions) {
    //     const auto toRow = fromRow + direction[0];
    //     const auto toCol = fromCol + direction[1];
    //     if (!Square::isValid(toRow, toCol)) {
    //         continue;
    //     }

    //     const auto to = Square(toRow, toCol);
    //     const auto toPiece = board.pieceAt(to).lock();
    //     if (to == move.to) {
    //         if (toPiece) {
    //             if (toPiece->getColour() != getColour()) {
    //                 return MoveType::Capture;
    //             }
    //         } else {
    //             return MoveType::Move;
    //         }
    //     }
    // }

    // // castling
    // const auto kingRow = getStartingRow();
    // const auto kingCol = 4;
    // const auto kingSquare = Square(kingRow, kingCol);
    // const auto kingsideRookSquare = Square(kingRow, 7);
    // const auto queensideRookSquare = Square(kingRow, 0);
    // if (!hasMoved() && move.from == kingSquare) {
    //     if (move.to == Square(kingRow, kingCol + 2)) {
    //         const auto kingsideRook = board.pieceAt(kingsideRookSquare).lock();
    //         if (kingsideRook && kingsideRook->getSymbol() == Constants::ROOK_SYMBOL && kingsideRook->getColour() == getColour() && !kingsideRook->hasMoved()) {
    //             auto squaresAreEmpty = true;
    //             for (auto col = kingSquare.col + 1; col < kingsideRookSquare.col; col++) {
    //                 if (board.pieceAt(Square(kingRow, col)).lock()) {
    //                     squaresAreEmpty = false;
    //                     break;
    //                 }
    //             }
    //             if (squaresAreEmpty) {
    //                 return MoveType::KingsideCastle;
    //             }
    //         }
    //     } else if (move.to == Square(kingRow, kingCol - 2)) {
    //         const auto queensideRook = board.pieceAt(queensideRookSquare).lock();
    //         if (queensideRook && queensideRook->getSymbol() == Constants::ROOK_SYMBOL && queensideRook->getColour() == getColour() && !queensideRook->hasMoved()) {
    //             auto squaresAreEmpty = true;
    //             for (auto col = kingSquare.col -  1; col > queensideRookSquare.col; col--) {
    //                 if (board.pieceAt(Square(kingRow, col)).lock()) {
    //                     squaresAreEmpty = false;
    //                     break;
    //                 }
    //             }
    //             if (squaresAreEmpty) {
    //                 return MoveType::QueensideCastle;
    //             }
    //         }
    //     }
    // }

    // return MoveType::None;
// }

auto King::getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> {
    auto legalMoves = std::vector<LegalMove>();
    const auto directions = std::vector<std::vector<int>>({{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
    for (const auto& direction : directions) {
        const auto toRow = from.row + direction[0];
        const auto toCol = from.col + direction[1];
        if (!Square::isValid(toRow, toCol)) {
            continue;
        }

        const auto to = Square(toRow, toCol);
        const auto toPiece = board.pieceAt(to).lock();
        if (toPiece) {
            if (toPiece->getColour() != getColour()) {
                const auto move = Move(from, to);
                legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::Capture });
            }
        } else {
            const auto move = Move(from, to);
            legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::Move });
        }
    }

    // castling
    const auto kingRow = getStartingRow();
    const auto kingCol = 4;
    const auto kingSquare = Square(kingRow, kingCol);
    const auto kingsideRookSquare = Square(kingRow, 7);
    const auto queensideRookSquare = Square(kingRow, 0);
    if (!hasMoved() && from == kingSquare) {
        // kingside
        const auto kingsideTo = Square(kingRow, kingCol + 2);
        const auto kingsideRook = board.pieceAt(kingsideRookSquare).lock();
        if (kingsideRook && kingsideRook->getSymbol() == Constants::ROOK_SYMBOL && kingsideRook->getColour() == getColour() && !kingsideRook->hasMoved()) {
            auto squaresAreEmpty = true;
            for (auto col = kingSquare.col + 1; col < kingsideRookSquare.col; col++) {
                if (board.pieceAt(Square(kingRow, col)).lock()) {
                    squaresAreEmpty = false;
                    break;
                }
            }
            if (squaresAreEmpty) {
                const auto move = Move(from, kingsideTo);
                legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::KingsideCastle });
            }
        }

        // queenside
        const auto queensideTo = Square(kingRow, kingCol - 2);
        const auto queensideRook = board.pieceAt(queensideRookSquare).lock();
        if (queensideRook && queensideRook->getSymbol() == Constants::ROOK_SYMBOL && queensideRook->getColour() == getColour() && !queensideRook->hasMoved()) {
            auto squaresAreEmpty = true;
            for (auto col = kingSquare.col -  1; col > queensideRookSquare.col; col--) {
                if (board.pieceAt(Square(kingRow, col)).lock()) {
                    squaresAreEmpty = false;
                    break;
                }
            }
            if (squaresAreEmpty) {
                const auto move = Move(from, queensideTo);
                legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::QueensideCastle });
            }
        }
    }

    return legalMoves;
}
