#include "gmock/gmock.h"
#include "PortfolioSln.h"
#include "StockService.h"

#include <string>

using namespace testing;
using namespace std;

class PortfolioTestSln : public Test
{
public:
    PortfolioSln portfolio;
    static const string Symantec;
    static const unsigned int SymantecCurrentValue;
    static const string Apple;

    void ASSERT_SIZE(unsigned int expected)
    {
        ASSERT_THAT(portfolio.Size(), Eq(expected));
        ASSERT_THAT(portfolio.IsEmpty(), Eq(expected == 0));
    }
    void SetUp() {}
    void TearDown() {}
};

const string PortfolioTestSln::Symantec("SYMC");
const unsigned int PortfolioTestSln::SymantecCurrentValue(19);
const string PortfolioTestSln::Apple("AAPl");

TEST_F(PortfolioTestSln, IsEmptyOnCreation)
{
    ASSERT_THAT(portfolio.IsEmpty(), Eq(true));
}

TEST_F(PortfolioTestSln, SizeIsZeroOnCreation)
{
    ASSERT_THAT(portfolio.Size(), Eq(0));
}

TEST_F(PortfolioTestSln, SizeIsOneAfterFirstPurchase)
{
    int shares(10);
    portfolio.Purchase(Symantec, shares);

    ASSERT_THAT(portfolio.Size(), Eq(1));
}

TEST_F(PortfolioTestSln, SizeIncrementsOnAdditionalPurchasDifferentSymbol)
{
    portfolio.Purchase(Symantec, 10);
    portfolio.Purchase(Apple, 10);

    ASSERT_THAT(portfolio.Size(), Eq(2));
}

TEST_F(PortfolioTestSln, SizeDoesNotIncreaseWhenSameSymbolPurchased)
{
    portfolio.Purchase(Symantec, 10);
    portfolio.Purchase(Symantec, 10);

    ASSERT_SIZE(1);
}

TEST_F(PortfolioTestSln, AnswersSharesForPurchasedSymbol)
{
    portfolio.Purchase(Symantec, 56);

    ASSERT_THAT(portfolio.Shares(Symantec), Eq(56));
}

TEST_F(PortfolioTestSln, AnswersZeroForSharesOfUnpurchasedSymbol)
{
    ASSERT_THAT(portfolio.Shares(Symantec), Eq(0));
}

TEST_F(PortfolioTestSln, SeparatesSharesBySymbol)
{
    portfolio.Purchase(Apple, 3);
    portfolio.Purchase(Symantec, 2);

    ASSERT_THAT(portfolio.Shares(Apple), Eq(3));
}

TEST_F(PortfolioTestSln, CombinesSharesForSameSymbol)
{
    portfolio.Purchase(Symantec, 70);
    portfolio.Purchase(Symantec, 52);

    ASSERT_THAT(portfolio.Shares(Symantec), Eq(122));
}

TEST_F(PortfolioTestSln, SellingSharesDeductsFromTotal)
{
    portfolio.Purchase(Symantec, 100);
    portfolio.Sell(Symantec, 32);

    ASSERT_THAT(portfolio.Shares(Symantec), Eq(68));
}

TEST_F(PortfolioTestSln, SellingAllSharesRemovesSymbol)
{
    portfolio.Purchase(Symantec, 100);
    portfolio.Sell(Symantec, 100);

    ASSERT_THAT(portfolio.Size(), Eq(0));
}

TEST_F(PortfolioTestSln, SellingTooManyThrowsException)
{
    int purchasedShares(5);
    portfolio.Purchase(Symantec, purchasedShares);

    ASSERT_THROW(portfolio.Sell(Symantec, purchasedShares + 1), std::exception);
}

TEST_F(PortfolioTestSln, ThrowsWhenSymbolIsEmpty)
{
    ASSERT_THROW(portfolio.Purchase("", 5), InvalidSymbolException);
}

TEST_F(PortfolioTestSln, ThrowsWhenSharesIsZero)
{
    try
    {
        portfolio.Purchase(Symantec, 0);
        FAIL();
    }
    catch (ZeroNotAllowedException expected)
    {
        ASSERT_THAT(portfolio.Size(), Eq(0));
    }
}

TEST_F(PortfolioTestSln, ValueIsNothingOnCreation)
{
    ASSERT_THAT(portfolio.Value(), Eq(0));
}

class StubLookupService : public StockService
{
public:
    virtual unsigned int CurrentPrice(const std::string& symbol)
    {
        //ASSERT_THAT(symbol, Eq(PortfolioTest::Symantec));
        if (symbol != PortfolioTestSln::Symantec)
            throw exception("symbol unexpected");
        return PortfolioTestSln::SymantecCurrentValue;
    }
};

TEST_F(PortfolioTestSln, IsWorthValueForSymbolOnPurchaseSingleShare)
{
    StubLookupService stubService;
    portfolio.SetStockLookupService(&stubService);
    portfolio.Purchase(Symantec, 1);

    ASSERT_THAT(portfolio.Value(), Eq(SymantecCurrentValue));
}
