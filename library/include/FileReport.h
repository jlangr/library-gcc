#ifndef FILE_REPORT_H
#define FILE_REPORT_H

#include <string>
#include <iostream>
#include <vector>

#include "Report.h"

class FileReport : public Report {
public:
    FileReport(std::string filename);
    virtual ~FileReport() {}

    std::string text() const override;
    std::string name() const override;
    void ftpGet();
    void load();
    std::vector<std::string> load(std::istream&);

private:
    bool _isLoaded{false};
    std::string _filename;
    std::string _name;
    std::string _text;
    const std::string FtpServer{"gatekeeper.dec.com"};

};

#endif
