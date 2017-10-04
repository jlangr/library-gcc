#include "gmock/gmock.h"
#include "restclient-cpp/restclient.h"
#include "json/json.h"

#include <string>
#include <thread>
#include <mutex>
#include <iostream>
#include <sstream>

using namespace std;
using namespace ::testing;

class Location {
public:
    Location(double lat, double lon): _lat{lat}, _lon{lon} {}
    virtual ~Location() {}

    void load() {
        auto response{get()};
        parse(response.body);
    }

    void parse(const string& response) {
        Json::Value root;
        stringstream s{ response };
        s >> root;
        _displayName = root["display_name"].asString();
        Json::Value address = root["address"];
        _city = address["city"].asString();
        _country = address["country"].asString();
    }

    string city() const {
        return _city;
    }

    string displayName() const {
        return _displayName;
    }

    string country() const {
        return _country;
    }

private:
    RestClient::Response get() {
        ostringstream url;
        url << "http://nominatim.openstreetmap.org/reverse.php?format=json"
            << "&lat=" << _lat
            << "&lon=" << _lon
            << "&zoom=17";
        return RestClient::get(url.str());
    }

    double _lat;
    double _lon;
    string _displayName;
    string _city{""};
    string _country{""};
};

TEST(ALocation, ParsesJson) {
    Location location{10, -45};

    auto response{"{\"display_name\": \"display name\", \"address\": {\"city\": \"London\", \"country\": \"UK\"}}"};

    location.parse(response);

    ASSERT_THAT(location.city(), StrEq("London"));
    ASSERT_THAT(location.country(), StrEq("UK"));
    ASSERT_THAT(location.displayName(), StrEq("display name"));
}

class Map {
public:
    void loadLocation(double lat, double lon) {
        auto loc{Location(lat, lon)};
        loc.load();
        _lock.lock();
        _locations.push_back(loc);
        _lock.unlock();
    }

    void loadLocations() {
        thread t1(&Map::loadLocation, this, 38.848698884981346, -104.852791428566);
        thread t2(&Map::loadLocation, this, 46.508732, 6.634088);

        cout << "LOADING!" << endl;

        t1.join();
        t2.join();

        cout << "LOADED!" << endl;
        for (auto loc: _locations)
            cout << loc.displayName() << endl
                << "\t" << loc.city() << ", " << loc.country() << endl;
    }

private:
    vector<Location> _locations;
    mutex _lock;
};


TEST(A, B) {
    Map map;
    //map.loadLocations();
    FAIL();
}

