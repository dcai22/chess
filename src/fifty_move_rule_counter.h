#pragma once

class FiftyMoveRuleCounter {
 private:
    double counter_ = 0;

 public:
    FiftyMoveRuleCounter();

    auto increment() noexcept -> void;
    auto reset() noexcept -> void;
    [[nodiscard]] auto isFulfilled() const noexcept -> bool;
};
