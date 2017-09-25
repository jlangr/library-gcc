#ifndef FILE_REPORT_H
#define FILE_REPORT_H

#include <string>
#include <iostream>
#include <vector>

#include "Report.h"

class FileReport /* : public Report */ {
public:
    FileReport(std::string filename);
    virtual ~FileReport() {}

    std::string text(); // override
    std::string name(); // override;
    void load();
    std::vector<std::string> load(std::istream&);

private:
//    File tempFile;
//    FileOutputStream localOutputStream;
    bool _isLoaded{false};
    std::string _filename;
    std::string _name;
    std::string _text;
    const std::string FtpServer{"ftp.somewhere.com"}; // "gatekeeper.dec.com";

};

#endif
