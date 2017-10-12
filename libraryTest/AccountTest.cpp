#include "gmock/gmock.h"

#include <vector>
#include <thread>

#include "Account.h"

using namespace std;
using namespace testing;

TEST(AnAccount, DISABLED_IncreasesBalanceOnDeposit) {
    int concurrentThreads{8};
    auto its{10000};
    auto amount{1000};
    for (auto i{0}; i < its; i++) {
       Account account;
       vector<thread> threads;
       for (int i = 0; i < concurrentThreads; ++i)
            threads.push_back(thread(&Account::deposit, &account, amount));
       for (auto& t: threads) t.join();

       auto val{account.balance()};

       ASSERT_THAT(val, Eq(concurrentThreads * amount));
    }
}

