#include "gmock/gmock.h"

#include <stdexcept>

#include "Portfolio.h"

using namespace testing;

class APortfolio: public Test {
public:
    Portfolio portfolio;
};

TEST_F(APortfolio, IsEmptyWhenCreated) {
    ASSERT_THAT(portfolio.empty(), Eq(true));
}

TEST_F(APortfolio, IsNotEmptyAfterPurchase) {
    portfolio.purchase("AAPL", 10);

    ASSERT_THAT(portfolio.empty(), Eq(false));
}

TEST_F(APortfolio, UniqueSymbolCountIsZeroWhenConstructed) {
    ASSERT_THAT(portfolio.uniqueSymbolCount(), Eq(0));
}

TEST_F(APortfolio, UniqueSymbolCountIncrementsWithEachPurchase) {
    portfolio.purchase("IBM", 42);
    ASSERT_THAT(portfolio.uniqueSymbolCount(), Eq(1));
    portfolio.purchase("AAPL", 44);
    ASSERT_THAT(portfolio.uniqueSymbolCount(), Eq(2));
}

TEST_F(APortfolio, DoesNotIncrementSymbolCountWithSameSymbolPurchase) {
    portfolio.purchase("IBM", 42);
    portfolio.purchase("IBM", 44);

    ASSERT_THAT(portfolio.uniqueSymbolCount(), Eq(1));
}

TEST_F(APortfolio, ReturnsSharesOfSymbolPurchased) {
    portfolio.purchase("AAPL", 10);

    ASSERT_THAT(portfolio.shares("AAPL"), Eq(10));
}

TEST_F(APortfolio, SeparatesSharesBySymbol) {
    portfolio.purchase("AAPL", 10);
    portfolio.purchase("IBM", 20);

    ASSERT_THAT(portfolio.shares("AAPL"), Eq(10));
}

TEST_F(APortfolio, AnswersZeroForSharesOfUnpurchasedSymbol) {
    ASSERT_THAT(portfolio.shares("ZEUS"), Eq(0));
}

TEST_F(APortfolio, SumsSharesBySymbol) {
    portfolio.purchase("AAPL", 10);
    portfolio.purchase("AAPL", 20);

    ASSERT_THAT(portfolio.shares("AAPL"), Eq(20 + 10));
}

TEST_F(APortfolio, ThrowsOnPurchaseOfZeroShares) {
    ASSERT_THROW(portfolio.purchase("AAPL", 0), std::runtime_error);
}
