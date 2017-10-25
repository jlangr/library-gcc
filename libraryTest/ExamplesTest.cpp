#include "gmock/gmock.h"

#include <string>
#include <vector>
#include <set>
#include <memory>
#include <exception>
#include <sstream>

using namespace std;
using namespace testing;

class Shape {};
class Circle: public Shape {};
class Ellipse: public Shape {};

class Auto {
public:
    void depressBrake() {}
    void pressStartButton() {}
    unsigned int RPM() {
        return 1000;
    }
};

TEST(Example, Assertions) {

  bool condition{false};
  string text{"something"};
  unsigned int idleSpeed{1001};
  string otherText{"something else"};


vector<string> newCollection;
ASSERT_THAT(newCollection, IsEmpty());

vector<int> items{0, 1, 2, 3};
ASSERT_THAT(items, SizeIs(4u));
ASSERT_THAT(items, Contains(2));
ASSERT_THAT(items, ElementsAre(0, Gt(0), Ne(1), _));

set<string> months{ "1712", "1710", "1711" };
ASSERT_THAT(months, UnorderedElementsAre("1710", "1711", "1712"));
ASSERT_THAT(months, Each(StartsWith("17")));

vector<string> allAlpha{ "alpha", "alpha" };
ASSERT_THAT(allAlpha, Each(Eq("alpha")));



  long value{0};
  int value2;
  int* pointer2{&value2};
  int* pointer1{nullptr};

  ASSERT_THAT(condition, Eq(false));
  ASSERT_THAT(text, Eq("something"));
  ASSERT_THAT(idleSpeed, Not(Eq(1000u)));
  ASSERT_THAT(idleSpeed, AllOf(Ge(950u), Le(1100u)));
  ASSERT_THAT(otherText, Ne("something"));


  ASSERT_THAT(pointer1, IsNull());
  ASSERT_THAT(pointer2, NotNull());

  //unique_ptr<Shape> shape{new Circle()};
//  Shape* shape = new Circle();
//  ASSERT_THAT(*shape, A<Shape>());
//  ASSERT_THAT(value2, A<std::string>());
//
  cout << value;
}


TEST(AnAutomobile, IdlesItsEngineWhenStarted) {
    Auto automobile;
    automobile.depressBrake();

    automobile.pressStartButton();

    ASSERT_THAT(automobile.RPM(), AllOf(Gt(950u), Lt(1100u)));
}

void loadData() {
    throw std::runtime_error("load error");
}

void parseData() {
}

void inject(int n) {
    if (n == 42) throw exception();
}

TEST(Example, ThrowsStuff) {
//    ASSERT_THROW(loadData(), std::runtime_error);
    ASSERT_NO_THROW(parseData());
    
    try {
        loadData();
        FAIL();
    }
    catch (runtime_error& e) {
        ASSERT_THAT(e.what(), StrEq("load error"));
    }

    ASSERT_ANY_THROW({ 
            int i{42};
            inject(i);
        });

}

TEST(Example, Strings) {
ASSERT_THAT("zara@swatch.ch", MatchesRegex(".*@.*\\.ch"));
ASSERT_THAT("jeff@langrsoft.com", ContainsRegex("@.*\\.com$"));
ASSERT_THAT("pix4d.com", EndsWith(".com"));
ASSERT_THAT("pix4d.com", StartsWith("pix4d"));
ASSERT_THAT("Arnold von Melchtal", HasSubstr(" von "));

ASSERT_THAT("pix4d", StrCaseEq("Pix4D"));
ASSERT_THAT("pix5d", StrCaseNe("Pix4D"));

ASSERT_THAT("olé", StrEq("olé"));
ASSERT_THAT("olé", StrNe("ole"));


string a{"hello"};
stringstream b;
b << "h";
b << "ello";
ASSERT_THAT(a, StrEq(b.str()));
ASSERT_THAT(a, Eq(b.str()));
}

class Item {
public:
    Item(string description, double price) : _description{description}, _price{price} {
    }
    bool isDiscountable() { return false; }
    string description() { return _description; }
    double price() { return _price; }
    void completeSale() { }

private:
    string _description;
    double _price;
};

class POS {
public:
void completeSale() {
    _registerMessages.clear();
    _total = 0.0;
    _totalOfDiscountedItems = 0.0;
    for (auto item : _purchases) {
        auto itemTotal = 0.0;
        stringstream message;
        if (item.isDiscountable()) {
            auto discounted = item.price() * (1 - _memberDiscount);
            _totalOfDiscountedItems += discounted;
            message << "item: " << item.description() <<
                    " price: " << item.price() <<
                    " discounted price: " << discounted;
            itemTotal += discounted;
        }
        else {
            itemTotal = item.price();
            message << "item: " << item.description() <<
                    " price: " << itemTotal;
        }
        _total += itemTotal;
        appendMessage(message.str());
        _registerMessages.push_back(message.str());
    }
}


void appendMessage(const std::string& message) {}
vector<Item> _purchases;
vector<string> _registerMessages;
double _memberDiscount{0.05};
double _total{0};
double _totalOfDiscountedItems{0};
};

class RefactoredPOS {
public:
void completeSale() {
    _registerMessages.clear();
    _total = 0.0;
    _totalOfDiscountedItems = 0.0;
    for (auto item : _purchases) {
        auto itemTotal = 0.0;
        stringstream message;
        if (item.isDiscountable()) {
            _totalOfDiscountedItems += discountedPrice(item);
            message << "item: " << item.description() <<
                    " price: " << item.price() <<
                    " discounted price: " << discountedPrice(item);
            itemTotal += discountedPrice(item);
        }
        else {
            itemTotal = item.price();
            message << "item: " << item.description() <<
                    " price: " << itemTotal;
        }
        _total += itemTotal;
        appendMessage(message.str());
        _registerMessages.push_back(message.str());
    }
}

private:
    double discountedPrice(Item& item) {
        return item.price() * (1 - _memberDiscount);
    }


void appendMessage(const std::string& message) {}
vector<Item> _purchases;
vector<string> _registerMessages;
double _memberDiscount{0.05};
double _total{0};
double _totalOfDiscountedItems{0};
};


class Result {};

class GreenerGrass {
public:
    Result doStuff(int n) { /* ... */ return Result(); }
    void doMoreStuff(Result& r) {}
    int answer() { return 1; }

    int comfortableMemberFunction(int someValue) {
        Result result = doStuff(someValue);
        doMoreStuff(result);
        return answer();
    }
};

class WrongPlace {
public:
    void client() {
        GreenerGrass grass;
        auto x{grass.comfortableMemberFunction(someValue())};
        // ...
        cout << x; // avoid compiler warning
    }

    void Client() {
        auto x{enviousMemberFunction()};
        // ...
        cout << x; // avoid compiler warning
    }

    int enviousMemberFunction() {
      GreenerGrass there;
      Result result = there.doStuff(someValue());
      there.doMoreStuff(result);
      return there.answer();
   }

   int someValue() { return 42; }
};

class DisplayDevice {
public:
    static void appendMessage(const string& message) {
        throw 1;
    }
};
class Register {
public:
    void completeSale() {
        _total = 0.0;
        for (auto purchase: _purchases) {
            string message{"item: " + purchase.description()};
            _total += purchase.price();
            appendMessage(message);
        }
    }

    double total() { 
        return _total;
    }

    void purchase(const string& description, double price) {
        _purchases.push_back(Item(description, price));
    }

    virtual void appendMessage(string& message) {
        DisplayDevice::appendMessage(message);
    }

private:
    double _total{0.0};
    vector<Item> _purchases;
};

TEST(POS2, Override) {
    class TestRegister: public Register {
    public:
        void appendMessage(string& message) override {}
    } posRegister;
    posRegister.purchase("milk", 42);

    posRegister.completeSale();

    ASSERT_THAT(posRegister.total(), Eq(42));
}

class VerificationService {
public:
};

class Verifier {
public:
    Verifier(int timeout, 
            VerificationService* verificationService = new VerificationService) 
        : _timeout{timeout}
        , _verificationService{verificationService} {}

    virtual ~Verifier() {
        delete _verificationService;
    }

private:
    int _timeout;
    VerificationService* _verificationService;
};


TEST(V, X) {
    class StubVerificationService: public VerificationService {
    public:
    };
    Verifier v{10, new StubVerificationService};
}
