#include "gmock/gmock.h"
#include "restclient-cpp/restclient.h"
#include "json/json.h"

#include <string>
#include <thread>
#include <mutex>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace ::testing;

class Location {
public:
    Location(double lat, double lon): _lat{lat}, _lon{lon} { } 
    virtual ~Location() {}

    void load() {
        auto response{get()};
        parse(toJsonValue(response.body));
    }

    Json::Value toJsonValue(const string& jsonText) {
        Json::Value root;
        stringstream s{ jsonText };
        s >> root;
        return root;
    }

    void parse(const Json::Value& root) {
        _displayName = root["display_name"].asString();
        Json::Value address = root["address"];
        _city = address["city"].asString();
        _country = address["country"].asString();
    }

    string coordinates() {
        stringstream s;
        s << "(" << _lat << "," << _lon << ")";
        return s.str();
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
        auto result = RestClient::get(url.str());
        return result;
    }

    double _lat;
    double _lon;
    string _displayName;
    string _city{""};
    string _country{""};
};

TEST(ALocation, DISABLED_ParsesJson) {
    Location location{10, -45};

    auto response{"{\"display_name\": \"display name\", \"address\": {\"city\": \"London\", \"country\": \"UK\"}}"};

    location.parse(response);

    ASSERT_THAT(location.city(), StrEq("London"));
    ASSERT_THAT(location.country(), StrEq("UK"));
    ASSERT_THAT(location.displayName(), StrEq("display name"));
}

class Map {
public:
    virtual ~Map() {
        for (auto loc: _locations)
            delete loc;
    }

    void addLocation(double lat, double lon) {
        _locations.push_back(new Location{lat, lon});
    }

    void loadLocations() {
        vector<thread> allThreads;
        for (auto loc: _locations)
            allThreads.push_back(move(thread(&Location::load, loc)));

        for (auto& t: allThreads)
            t.join();
    }

    vector<Location*> locations() {
        return _locations;
    }

private:
    vector<Location*> _locations;
};


TEST(AMap, CanStuff) {
    Map map;
    map.addLocation(38.848698884981346, -104.852791428566); // colorado springs
    map.addLocation(46.508732, 6.634088); // lausanne

    map.loadLocations();
    
    vector<string> cities;
    vector<Location*> locations = map.locations();
    transform(locations.begin(), locations.end(), back_inserter(cities),
            [](Location* loc) { return loc->city(); });

    ASSERT_THAT(cities, UnorderedElementsAre("Colorado Springs", "Lausanne"));
}

