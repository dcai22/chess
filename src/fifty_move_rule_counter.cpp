#include "fifty_move_rule_counter.h"

FiftyMoveRuleCounter::FiftyMoveRuleCounter() {
};

auto FiftyMoveRuleCounter::increment() -> void {
    counter_ += 0.5;
}

auto FiftyMoveRuleCounter::reset() -> void {
    counter_ = 0;
}

auto FiftyMoveRuleCounter::isFulfilled() const -> bool {
    return counter_ >= 50;
}
