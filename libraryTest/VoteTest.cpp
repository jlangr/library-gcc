#include "gmock/gmock.h"

#include <thread>

#include "Vote.h"
#include "VoteEngine.h"

using namespace testing;
using namespace std::chrono;
using namespace std;

const unsigned int AMessageId{1};
const unsigned int AClientId{10};

class AVoteEngine: public Test {
public:
    VoteEngine engine;

    void voteMany(const Vote& vote, int its) {
        for (int i = 0; i < its; i++)
            engine.accept(vote);
    }

    void downvote(int its) {
        voteMany(Vote::downvote(AMessageId, AClientId), its);
    }

    void upvote(int its) {
        voteMany(Vote::upvote(AMessageId, AClientId + its), its);
    }
};

TEST_F(AVoteEngine, AllowsUpvoteOnMessage) {
    engine.accept(Vote::upvote(AMessageId, AClientId));

    ASSERT_THAT(engine.count(AMessageId), Eq(1));
}

TEST_F(AVoteEngine, AllowsDownvoteOnMessage) {
    engine.accept(Vote::downvote(AMessageId, AClientId));

    ASSERT_THAT(engine.count(AMessageId), Eq(-1));
}

TEST_F(AVoteEngine, HasZeroForCountOnUnvotedMessage) {
    ASSERT_THAT(engine.count(AMessageId), Eq(0));
}

TEST_F(AVoteEngine, TracksVoteCountForMultipleMessages) {
    engine.accept(Vote::downvote(AMessageId, AClientId));
    engine.accept(Vote::upvote(AMessageId + 1, AClientId));

    ASSERT_THAT(engine.count(AMessageId), Eq(-1));
}

TEST_F(AVoteEngine, SumsMultipleVotes) {
    engine.accept(Vote::upvote(AMessageId, AClientId));
    engine.accept(Vote::upvote(AMessageId, AClientId + 1));
    engine.accept(Vote::upvote(AMessageId, AClientId + 2));
    engine.accept(Vote::downvote(AMessageId, AClientId + 3));

    ASSERT_THAT(engine.count(AMessageId), Eq(2));
}

// future feature
/*
TEST_F(AVoteEngine, DISABLED_IgnoresMultipleUpvotesOnSameMessage) {
    engine.accept(Vote::upvote(AMessageId, AClientId));
    engine.accept(Vote::upvote(AMessageId, AClientId));

    ASSERT_THAT(engine.count(AMessageId), Eq(1));
}
*/

TEST_F(AVoteEngine, DISABLED_SupportsConcurrency) {
    auto its{10000};
    auto concurrentThreadPairs{1};
    vector<thread> threads;
    for (int i = 0; i < concurrentThreadPairs; i++) {
        threads.push_back(thread([&]() { downvote(its); }));
        threads.push_back(thread([&]() { upvote(its); }));
    }
    for (auto& t: threads) t.join();

    auto count{engine.count(AMessageId)};

    ASSERT_THAT(count, Eq(0));
}
