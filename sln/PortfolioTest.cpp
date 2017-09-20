#include "gmock/gmock.h"

#include <memory>

#include "StockService.h"
#include "Portfolio.h"

using namespace testing;

class APortfolio : public Test
{
public:
    Portfolio portfolio;
};

TEST_F(APortfolio, HasNoHoldingsWhenCreated)
{
    ASSERT_THAT(portfolio.Size(), Eq(0));
}

TEST_F(APortfolio, HasHoldingsAfterPurchase)
{
    portfolio.Purchase("IBM", 10);

    ASSERT_THAT(portfolio.Size(), Eq(1));
}

TEST_F(APortfolio, SizeIncreasesWithNewUniqueSymbol)
{
    portfolio.Purchase("IBM", 10);
    portfolio.Purchase("AAPL", 20);

    ASSERT_THAT(portfolio.Size(), Eq(2));
}

TEST_F(APortfolio, SizeDoesNotIncreaseForDuplicateSymbolPurchase)
{
    portfolio.Purchase("IBM", 10);
    portfolio.Purchase("IBM", 20);

    ASSERT_THAT(portfolio.Size(), Eq(1));
}

TEST_F(APortfolio, AnswersSharesPurchasedForSymbol)
{
    portfolio.Purchase("IBM", 10);

    ASSERT_THAT(portfolio.Shares("IBM"), Eq(10));
}

TEST_F(APortfolio, SeparatesSharesBySymbol)
{
    portfolio.Purchase("IBM", 10);
    portfolio.Purchase("AAPL", 20);

    ASSERT_THAT(portfolio.Shares("IBM"), Eq(10));
}

TEST_F(APortfolio, AnswersZeroForSharesOfSymbolNotPurchased)
{
    ASSERT_THAT(portfolio.Shares("IBM"), Eq(0));
    // This is not needed if Shares is a const function
    //ASSERT_THAT(portfolio.Size(), Eq(0));
}

TEST_F(APortfolio, ReturnsTotalSharesForSymbol)
{
    portfolio.Purchase("IBM", 10);
    portfolio.Purchase("IBM", 20);

    ASSERT_THAT(portfolio.Shares("IBM"), Eq(30));
}

TEST_F(APortfolio, ThrowsOnPurchaseOfEmptySymbol)
{
    ASSERT_ANY_THROW(portfolio.Purchase("", 1));
}

TEST_F(APortfolio, ThrowsOnPurchaseOfZeroShares)
{
    ASSERT_THROW(portfolio.Purchase("IBM", 0), InvalidSharesException);
}

TEST_F(APortfolio, ThrowsOnPurchaseOfEmptySymbolOldSchool)
{
    try {
        portfolio.Purchase("", 1);
        FAIL();
    }
    catch (...)
    {
    }
}

TEST_F(APortfolio, IsWorthlessOnCreation)
{
    ASSERT_THAT(portfolio.Value(), Eq(0));
}

class FakeStockService : public StockService
{
public:
    static const unsigned int IbmPrice{ 10 };
    static const unsigned int ApplePrice{ 10 };
    unsigned int CurrentPrice(const std::string& symbol)
    {
        if ("AAPL" == symbol) return ApplePrice;
        if ("IBM" == symbol) return IbmPrice;
        return 0;
    }
};

TEST_F(APortfolio, ValueForSingleHoldingIsPriceTimesShares)
{
    unique_ptr<StockService> fakeStockService{ new FakeStockService() };
    portfolio.SetStockService(fakeStockService.get());

    portfolio.Purchase("IBM", 20);

    ASSERT_THAT(portfolio.Value(), Eq(20 * FakeStockService::IbmPrice));
}

TEST_F(APortfolio, ValueForMultipleHoldingsDoesSum)
{
    unique_ptr<StockService> fakeStockService{ new FakeStockService() };
    portfolio.SetStockService(fakeStockService.get());

    portfolio.Purchase("IBM", 20);
    portfolio.Purchase("AAPL", 30);

    ASSERT_THAT(portfolio.Value(),
        Eq(20 * FakeStockService::IbmPrice +
            30 * FakeStockService::ApplePrice));
}

class MockStockService : public StockService
{
public:
    MOCK_METHOD1(CurrentPrice, unsigned int(const std::string&));
};


TEST_F(APortfolio, ValueForMultipleHoldingsDoesSumUsingMock)
{
    unique_ptr<MockStockService> fakeStockService{ new MockStockService() };
    EXPECT_CALL(*fakeStockService.get(), CurrentPrice("IBM"))
        .WillOnce(Return(FakeStockService::IbmPrice));
    EXPECT_CALL(*fakeStockService.get(), CurrentPrice("AAPL"))
        .WillOnce(Return(FakeStockService::ApplePrice));
    portfolio.SetStockService(fakeStockService.get());

    portfolio.Purchase("IBM", 20);
    portfolio.Purchase("AAPL", 30);

    ASSERT_THAT(portfolio.Value(),
        Eq(20 * FakeStockService::IbmPrice +
            30 * FakeStockService::ApplePrice));
}