#ifndef SoundexListenerH
#define SoundexListenerH

#include "gmock/gmock.h"
#include <string>
#include <vector>

#include "Soundex.h"

using namespace testing;
using namespace std;

// this class is bad, hastily hacked-together, non TDD code

struct AssertEq {
    AssertEq() {}
    AssertEq(const string& convertArg, const string& expected)
        : ConvertArg(convertArg)
        , Expected(expected)
    {
    }

    string ConvertArg;
    string Expected;
};
struct TestTracker
{
    TestTracker() {}
    TestTracker(const string& name, int order)
        : Name(name)
        , Order(order)
        , WasExecuted(false)
    {
    }

    void AddAssertEq(const string& convertArg, const string& expected ) 
    {
        AssertEq assertEq(convertArg, expected);
        assertEqs.push_back(assertEq);
    }

    vector<AssertEq> assertEqs;
    string Name;
    bool WasExecuted;
    bool Passed;
    int Order;
};

class SoundexListener: public EmptyTestEventListener
{
public:
    SoundexListener()
    {
        PopulateTests();
    }
    ~SoundexListener()
    {
        //for (map<string,TestTracker*>::iterator it = mTests.begin();
        //    it != mTests.end();
        //    it++)
        //{
        //    delete it->second;
        //}
    }

    void OnTestEnd(const TestInfo& testInfo)
    {
        if (strcmp(testInfo.test_case_name(), "SoundexTest") == 0)
        {
            string testName = string(testInfo.name());
            TestTracker* tracker = findTracker(testName);
            if (tracker == NULL)
                return;
            tracker->WasExecuted = true;
            tracker->Passed = testInfo.result()->Passed();
        }
    }

    void AddAssertEq(const string& name, const string& convertArg, const string& expected)
    {
        TestTracker* tracker = findTracker(name);
        tracker->AddAssertEq(convertArg, expected);
    }

    void PopulateTests()
    {
        AddTestTracker("AppendsThreeTrailingZerosIfSingleLetter",0);
        AddTestTracker("RetainsFirstLetter", 1);
        AddTestTracker("ConvertsHardSoundsUsingLookupTable" ,2);
        AddTestTracker("IgnoresSoftSounds" ,3);
        AddTestTracker("DoesNotAppendZerosIfAlreadyFourCharacters" ,4);
        AddTestTracker("StopsAfterFourCharacters" ,5);
        AddTestTracker("PadsWithZerosToEnsureThreeDigits" ,6);
        AddTestTracker("IgnoresDuplicateHardSounds" ,7);
        AddTestTracker("HardSoundNotIgnoredIfVowelPrecedesIt" ,8);
        AddTestTracker("HardSoundIgnoredIfSoftConsonantPrecedesIt" ,9);
        AddAssertEq("AppendsThreeTrailingZerosIfSingleLetter","A", "A000");
        AddAssertEq("RetainsFirstLetter", "B", "B000");
        AddAssertEq("ConvertsHardSoundsUsingLookupTable", "Abcd", "A123000");
        AddAssertEq("ConvertsHardSoundsUsingLookupTable", "Afgt", "A123000");
        AddAssertEq("ConvertsHardSoundsUsingLookupTable", "Apjd", "A123000");
        AddAssertEq("ConvertsHardSoundsUsingLookupTable", "Avkd", "A123000");
        AddAssertEq("ConvertsHardSoundsUsingLookupTable", "Abqd", "A123000");
        AddAssertEq("ConvertsHardSoundsUsingLookupTable", "Absd", "A123000");
        AddAssertEq("ConvertsHardSoundsUsingLookupTable", "Abxd", "A123000");
        AddAssertEq("ConvertsHardSoundsUsingLookupTable", "Abzd", "A123000");
        AddAssertEq("ConvertsHardSoundsUsingLookupTable", "Almr", "A456000");
        AddAssertEq("ConvertsHardSoundsUsingLookupTable", "Alnr", "A456000");
        //AddAssertEq("IgnoresSoftSounds", "Aaei", "A000");
        //AddAssertEq("IgnoresSoftSounds", "Aouy", "A000");
        //AddAssertEq("IgnoresSoftSounds", "Ahwe", "A000");
        AddAssertEq("DoesNotAppendZerosIfAlreadyFourCharacters", "Arml", "A654");
        AddAssertEq("StopsAfterFourCharacters", "Armlrml", "A654");
        AddAssertEq("PadsWithZerosToEnsureThreeDigits", "Af", "A100");
        AddAssertEq("IgnoresDuplicateHardSounds", "Acgbm", "A215");
        AddAssertEq("HardSoundNotIgnoredIfVowelPrecedesIt", "Acogbm", "A221");
        AddAssertEq("HardSoundIgnoredIfSoftConsonantPrecedesIt", "Acwgbm", "A215");
    }

    void AddTestTracker(const string& name, int order)
    {
        TestTracker* tracker = new TestTracker(name, order);
        mTests[name] = tracker;
        mOrderedTests[order] = name;
    }

    TestTracker* findTracker(string name)
    {
        return mTests[name];
    }

    void OnTestIterationEnd(const UnitTest& unit_test, int iteration) 
    {
        if (unit_test.failed_test_count() > 0)
            return;

        string highOrder = HighOrderTestName();
        if (highOrder != "")
        {
            TestTracker* tracker = mTests[highOrder];
            if (tracker->Order < 9)
            {
                TestTracker* next = findTracker(mOrderedTests[tracker->Order + 1]);

                Soundex soundex;
                for (vector<AssertEq>::iterator it = next->assertEqs.begin();
                    it != next->assertEqs.end();
                    it++)
                {
                    AssertEq assertEq = *it;
                    if (soundex.Convert(assertEq.ConvertArg) == assertEq.Expected)
                    {
                        stringstream s;
                        s << "You've implemented too much functionality! " << endl
                          << "Your solution allows Convert(\"" << assertEq.ConvertArg 
                          << "\") to generate \"" << assertEq.Expected << "\" (in test " << next->Name << ")" << endl;
                        cout << s.str();
                        FAIL();
                    }
                }
            }
        }
    }

    string HighOrderTestName()
    {
        int highOrder = -1;
        string highTest("");
        for (map<string,TestTracker*>::iterator it = mTests.begin();
            it != mTests.end();
            it++)
        {
            TestTracker* tracker = it->second;
            if (tracker->WasExecuted && tracker->Passed) {
                if (tracker->Order > highOrder) {
                    highOrder = tracker->Order;
                    highTest = tracker->Name;
                }
            }
        }
        return highTest;
    }

    map<string,TestTracker*> mTests;
    string mOrderedTests[10];
};

#endif
