#include "fifty_move_rule_counter.h"

FiftyMoveRuleCounter::FiftyMoveRuleCounter() {
};

auto FiftyMoveRuleCounter::increment() noexcept -> void {
    counter_ += 0.5;
}

auto FiftyMoveRuleCounter::reset() noexcept -> void {
    counter_ = 0;
}

auto FiftyMoveRuleCounter::isFulfilled() const noexcept -> bool {
    return counter_ >= 50;
}
