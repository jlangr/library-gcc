#include "FileReport.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

FileReport::FileReport(std::string filename): _filename{filename} {
    // copy filename from remote server
//        FTPClient ftp;
//        FTPClientConfig config;
//        ftp.configure(config);
    bool error{false};
    try {
//            int reply;
//            ftp.connect(FtpServer);
//            reply = ftp.getReplyCode();
//            cout << "reply code:" << reply << endl;
//
//            if (!FTPReply.isPositiveCompletion(reply)) {
//                ftp.disconnect();
//                throw runtime_error("FTP server refused connection");
//            }
//
//            ftp.login("ftp", "");
//
//            // transfer files
//            ftp.setFileType(FTP.BINARY_FILE_TYPE);
//
//            InputStream inputStream = ftp.retrieveFileStream("robots.txt");

        ofstream localOutputStream{"local.txt", ios::out};
        std::string content{"123\n123\n3rd\n4th\n"};
        localOutputStream << content;
        localOutputStream.close();

//            localOutputStream = new FileOutputStream("local.txt");
//            IOUtils.copy(inputStream, localOutputStream);
//            localOutputStream.flush();
//            IOUtils.closeQuietly(localOutputStream);
//            IOUtils.closeQuietly(inputStream);

//            ftp.logout();
    }

}

string FileReport::text() {
    if (!_isLoaded) {
        load();
    }
    return _text;
}

string FileReport::name() {
    if (!_isLoaded) {
        load();
    }
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
        throw runtime_error("unable to load"); // cause?
    }
}

