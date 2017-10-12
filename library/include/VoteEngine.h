#ifndef VoteEngine_H
#define VoteEngine_H

#include <unordered_map>

#include "Vote.h"

class VoteEngine {
public:
    void accept(const Vote& vote) {
        auto currentCount{_counts[vote._messageId]};
        auto delta{vote._isUpvote ? 1 : -1};
        _counts[vote._messageId] = currentCount + delta;
    }

    int count(unsigned int messageId) const {
        auto it{_counts.find(messageId)};
        if (it == _counts.end()) return 0;
        return it->second;
    }

private:
    std::unordered_map<unsigned int,int> _counts;
};

#endif
