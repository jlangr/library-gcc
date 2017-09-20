#pragma once

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Parser
{
public:
    enum ParserState 
    {
        StateInitial,
        StateList,
        StateError,
        StateCloseList,
        StateKeyStart,
        StateKeyEnd,
        StateKeyData,
        StateValue,
        StateStringStart,
    };

    Parser(void) 
        : mState(StateInitial)
    {
    }

    ~Parser(void) {}

    ParserState CurrentState() { return mState; }
    void SetCurrentState(ParserState state) { mState = state; }

    string LastToken()
    {
        return mToken.str();
    }

    void Parse(const std::string& input)
    {
        unsigned int i = 0;
        while (CurrentState() != StateError && i < input.length())
        {
            Accept(input[i++]);
        }
    }

    // return what?
    vector<pair<string,string>> CurrentList()
    {
        vector<pair<string, string>> list;
        return list;
    }

    void Accept(char c)
    {
        switch (CurrentState())
        {
            case StateInitial:
                InitialAccept(c);
                break;
            case StateList:
                ListAccept(c);
                break;
            case StateError:
                break;
            case StateKeyStart:
                KeyStartAccept(c);
                break;
            case StateKeyData:
                KeyDataAccept(c);
                break;
            case StateKeyEnd:
                KeyEndAccept(c);
                break;
            case StateValue:
                ValueAccept(c);
                break;
            default:
                break;
        }
    }

    void InitialAccept(char c)
    {
        if (c == '(')
            mState = StateList;
        else
            mState = StateError;
    }

    void ListAccept(char c)
    {
        if (c == ')')
            mState = StateCloseList;
        else if (c == '"')
            mState = StateKeyStart;
    }

    void KeyStartAccept(char c)
    {
        mState = StateKeyData;
        KeyDataAccept(c);
    }

    void KeyDataAccept(char c)
    {
        if (c == '"')
            mState = StateKeyEnd;
        else
            mToken << c;
    }

    void KeyEndAccept(char c)
    {
        if (c == '=')
            mState = StateValue;
        else
            mState = StateError;
    }

    void ValueAccept(char c)
    {
        if (c == '"')
            mState = StateStringStart;
    }

private:
    enum ParserState mState;
    stringstream mToken;
    vector<ParserState> mStates;
};
