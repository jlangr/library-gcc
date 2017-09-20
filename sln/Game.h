#pragma once

class Game
{
public:
    Game() : mCurrentRoll(0) {
        for (int i = 0; i < 21; i++)
            rolls[i] = 0;
    }

    void AddRoll(unsigned int pins)
    {
        rolls[mCurrentRoll++] = pins;
    }

    unsigned int Score()
    {
        unsigned int total(0);
        for (unsigned int roll = 0; roll < mCurrentRoll; )
        {
            total += Current(roll) + Next(roll);
            if (IsStrike(roll))
            {
                total += Following(roll);
                roll += 1;
            }
            else {
                if (IsSpare(roll))
                    total += Following(roll);
                roll += 2;
            }
        }
        return total;
    }

    unsigned int Current(unsigned int roll)
    {
        return rolls[roll];
    }

    unsigned int Following(unsigned int roll)
    {
        return rolls[roll + 2];
    }

    unsigned int Next(unsigned int roll)
    {
        return rolls[roll + 1];
    }

    bool IsSpare(unsigned int roll)
    {
        return rolls[roll] + rolls[roll + 1] == 10;
    }

    bool IsStrike(unsigned int roll)
    {
        return rolls[roll] == 10;
    }

private:
    int rolls[21];
    unsigned int mCurrentRoll;
};
