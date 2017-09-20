#include "gmock/gmock.h"
#include "Game.h"

using namespace testing;

class BowlingTest: public Test
{
public:
    Game game;

    void AddRolls(Game& game, unsigned int pins, unsigned int times)
    {
        for (unsigned int i = 0; i < times; i++)
            game.AddRoll(pins);
    }
};

TEST_F(BowlingTest, AllGutterBalls)
{
    AddRolls(game, 0, 20);

    ASSERT_EQ(0, game.Score());
}

TEST_F(BowlingTest, SomePinsOnFirstRollThenNothing)
{
    game.AddRoll(5);

    ASSERT_EQ(5, game.Score());
}

TEST_F(BowlingTest, AddsPinsIntoTotalAcrossAllFrames)
{
    game.AddRoll(5);
    game.AddRoll(3);
    game.AddRoll(2);
    game.AddRoll(0);
    game.AddRoll(3);
    game.AddRoll(3);

    ASSERT_EQ(5+3+2+0+3+3, game.Score());
}

TEST_F(BowlingTest, CanHandleASpare)
{
    game.AddRoll(4);
    game.AddRoll(6);
    game.AddRoll(3);

    ASSERT_EQ((4 + 6 + 3) + 3, game.Score());
}


TEST_F(BowlingTest, CanHandleAStrike)
{
    game.AddRoll(10);
    game.AddRoll(6);
    game.AddRoll(3);

    ASSERT_EQ((10 + 6 + 3) + 6 + 3, game.Score());
}