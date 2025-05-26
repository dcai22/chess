#pragma once

#include <optional>
#include <vector>
#include <unordered_map>
#include <string>

#include "board.h"
#include "types.h"
#include "fifty_move_rule_counter.h"

class Game {
 private:
    Board board_ = Board();
    PieceColour colourToMove_ = PieceColour::White;
    std::vector<Move> moves_ = std::vector<Move>();
    std::vector<LegalMove> legalMoves_;
    bool hasEnded_ = false;
    std::optional<PieceColour> winner_ = std::nullopt;
    std::optional<Square> enPassantTarget_ = std::nullopt;
    bool whiteCanCastleKingside_ = true;
    bool whiteCanCastleQueenside_ = true;
    bool blackCanCastleKingside_ = true;
    bool blackCanCastleQueenside_ = true;
    std::unordered_map<std::string, int> seenPositions_ = std::unordered_map<std::string, int>();
    FiftyMoveRuleCounter fiftyMoveRuleCounter_ = FiftyMoveRuleCounter();
    
    auto updateLegalMoves() -> void;
    [[nodiscard]] auto validateLegalMove(const LegalMove& legalMove) const -> bool;
    [[nodiscard]] auto validateEnPassant(const Move& move) const -> bool;
    [[nodiscard]] auto validateCastle(const Move& move) const -> bool;
    [[nodiscard]] auto getMoveType(const Move& move) const -> MoveType;
    auto updateCastlingRights(const Move& move) -> void;
    auto revokeKingsideCastleRights(const PieceColour& colour) -> void;
    auto revokeQueensideCastleRights(const PieceColour& colour) -> void;
    auto updateSeenPositions() -> int; // returns number of times the position has been seen
    [[nodiscard]] auto isPawnMoveOrCapture(const LegalMove& legalMove) -> bool;

    public:
    Game();

    auto processMove(const Move& move) -> bool;
    auto printBoard() const -> void;

    [[nodiscard]] auto getWinner() const -> std::optional<PieceColour>;
    [[nodiscard]] auto hasEnded() const -> bool;
    [[nodiscard]] auto getColourToMove() const -> PieceColour;
};
