#pragma once

#include <optional>
#include <vector>

#include "board.h"
#include "types.h"

class Game {
 private:
    Board board_ = Board();
    PieceColour colourToMove_ = PieceColour::White;
    std::vector<Move> moves_ = std::vector<Move>();
    std::vector<LegalMove> legalMoves_;
    bool hasEnded_ = false;
    std::optional<PieceColour> winner_ = std::nullopt;

    auto updateLegalMoves() -> void;
    auto validateLegalMove(const LegalMove& legalMove) const -> bool;
    auto validateEnPassant(const Move& move) const -> bool;
    auto validateCastle(const Move& move) const -> bool;
    auto getMoveType(const Move& move) const -> MoveType;
    
    public:
    Game();
    
    auto processMove(const Move& move) -> bool;
    auto printBoard() const -> void;
    
    auto getWinner() const -> std::optional<PieceColour>;
    auto hasEnded() const -> bool;
    auto getColourToMove() const -> PieceColour;
};
