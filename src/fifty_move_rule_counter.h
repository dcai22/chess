#pragma once

class FiftyMoveRuleCounter {
 private:
    double counter_ = 0;

 public:
    FiftyMoveRuleCounter();

    auto increment() -> void;
    auto reset() -> void;
    auto isFulfilled() const -> bool;
};
