#include "gmock/gmock.h"

#include <vector>
#include <string>

#include "Parser.h"

using namespace std;
using namespace testing;

class ParserTest: public Test
{
public:
    Parser parser;

    void ASSERT_STATE(Parser::ParserState expected)
    {
        ASSERT_THAT(parser.CurrentState(), Eq(expected));
    }
};

TEST_F(ParserTest, IsInInitialStateOnCreation)
{
    ASSERT_STATE(Parser::StateInitial);
}

TEST_F(ParserTest, InitialeMovesToListOnParen)
{
    parser.Accept('(');

    ASSERT_STATE(Parser::StateList);
}

TEST_F(ParserTest, InitialErrsNotParen)
{
    parser.Accept('x');

    ASSERT_STATE(Parser::StateError);
}

TEST_F(ParserTest, ParsesStringUntilError)
{
    parser.Parse("x");

    ASSERT_STATE(Parser::StateError);
}

// ("X"="Y")
TEST_F(ParserTest, ListMovesToCloseListOnRightParen)
{
    parser.SetCurrentState(Parser::StateList);

    parser.Accept(')');

    ASSERT_STATE(Parser::StateCloseList);
}

TEST_F(ParserTest, AnswersParsedPairsOnCloseList)
{
    parser.Parse("()");

    vector<pair<string,string>> pairs = parser.CurrentList();
    ASSERT_EQ(0, pairs.size());
}

TEST_F(ParserTest, ListMovesToKeyStartOnQuote)
{
    parser.SetCurrentState(Parser::StateList);

    parser.Accept('"');

    ASSERT_STATE(Parser::StateKeyStart);
}

TEST_F(ParserTest, KeyStartMovesToKeyDataOnAnything)
{
    parser.SetCurrentState(Parser::StateKeyStart);

    parser.Accept('A');

    ASSERT_STATE(Parser::StateKeyData);
}

TEST_F(ParserTest, KeyDataMovesToKeyEndOnQuote)
{
    parser.SetCurrentState(Parser::StateKeyData);

    parser.Accept('"');

    ASSERT_STATE(Parser::StateKeyEnd);
}

TEST_F(ParserTest, KeyDataHoldsStateOnAllElse)
{
    parser.SetCurrentState(Parser::StateKeyData);

    parser.Accept('B');

    ASSERT_STATE(Parser::StateKeyData);
}


TEST_F(ParserTest, TokenAvailableOnKeyEnd)
{
    parser.Parse("(\"Abc\"");

    ASSERT_THAT(parser.LastToken(), Eq("Abc"));
}

TEST_F(ParserTest, KeyEndMovesToValueStateOnEqual)
{
    parser.SetCurrentState(Parser::StateKeyEnd);

    parser.Accept('=');

    ASSERT_STATE(Parser::StateValue);
}

TEST_F(ParserTest, KeyEndErrsOnAllElse)
{
    parser.SetCurrentState(Parser::StateKeyEnd);

    parser.Accept('x');

    ASSERT_STATE(Parser::StateError);
}

// empty string? ""

TEST_F(ParserTest, ValueMovesToStringStartOnQuote)
{
    parser.SetCurrentState(Parser::StateValue);

    parser.Accept('"');

    ASSERT_STATE(Parser::StateStringStart);
}