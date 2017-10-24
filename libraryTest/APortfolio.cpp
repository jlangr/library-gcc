#include "gmock/gmock.h"

#include <stdexcept>

#include "Portfolio.h"
#include "StockService.h"

using namespace testing;

const unsigned int IbmCurrentValue{200};
const unsigned int AaplCurrentValue{250};

class StubStockService: public StockService {
    unsigned int currentPrice(const std::string& symbol) {
        if ("IBM" == symbol) return IbmCurrentValue;
        if ("AAPL" == symbol) return AaplCurrentValue;
        throw 1;
    }
};

class APortfolio: public Test {
public:
    StubStockService stubStockService;
    Portfolio portfolio{&stubStockService};
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

TEST_F(APortfolio, IsWorthlessWhenCreated) {
    ASSERT_THAT(portfolio.value(), Eq(0));
}

// does this test retain value?
TEST_F(APortfolio, IsWorthSharePriceForSingleSharePurchase) {
    portfolio.purchase("IBM", 1);

    ASSERT_THAT(portfolio.value(), Eq(IbmCurrentValue));
}

TEST_F(APortfolio, ValueMultipliesSharePriceByShares) {
    portfolio.purchase("IBM", 10);

    // uh oh, implicit expectations!
    ASSERT_THAT(portfolio.value(), Eq(IbmCurrentValue * 10));
}

TEST_F(APortfolio, ValueSumsValuesBySymbol) {
    portfolio.purchase("IBM", 10);
    portfolio.purchase("AAPL", 20);

    ASSERT_THAT(portfolio.value(), Eq(IbmCurrentValue * 10 +
                                      AaplCurrentValue * 20));
}
