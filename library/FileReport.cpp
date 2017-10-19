#include "FileReport.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>

#include "ftplib.h"

using namespace std;

FileReport::FileReport(std::string filename): _filename{filename} {
    ftpGet();
    load();
}

void FileReport::ftpGet() {
    ftplib ftp;
    auto connect = ftp.Connect(FtpServer.c_str());
    if (!connect) {
        throw runtime_error("unable to connect to " + FtpServer);
    }
    auto error{false};
    auto loginSuccess = ftp.Login("ftp", "");
    if (!loginSuccess) {
        ftp.Quit();
        throw runtime_error("unable to log in");
    }
    ftp.Get("local.txt", "robots.txt", ftplib::transfermode::ascii, 0);
    ftp.Quit();
}

string FileReport::text() const {
    return _text;
}

string FileReport::name() const {
    return _name;
}

void FileReport::load() {
    try {
        ifstream reader("local.txt", ios::in);
        vector<string> list = load(reader);
        _name = list[0];
        _text = list[1];
        _isLoaded = true;
    } catch (exception& e) {
        throw runtime_error("");
    }
}

vector<string> FileReport::load(istream& reader) {
    try {
        vector<string> report;

        string first;
        getline(reader, first);
        report.push_back(first);

        stringstream buffer;
        string line;

        while (getline(reader, line)) {
            buffer << line;
            buffer << "\n";
        }
        string rest{buffer.str()};
        report.push_back(rest);
        return report;
    } catch (exception& e) {
        throw runtime_error("unable to load");
    }
}

