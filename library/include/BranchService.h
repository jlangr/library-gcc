#ifndef BRANCH_SERVICE_H
#define BRANCH_SERVICE_H

#include <exception>

#include "BranchAccess.h"

class DuplicateBranchNameException: public std::exception {
public:
    DuplicateBranchNameException(void) {};
    ~DuplicateBranchNameException() {};
};

class BranchService
{
public:
    BranchService(void);
    virtual ~BranchService(void);

    static void deleteAll();

    void add(Branch& branch);
    std::string add(const std::string& name, const std::string& address);
    short branchCount() const;
    bool find(Branch& branch) const;
    bool existsWithName(const std::string& name) const;

private:
    BranchAccess mBranchAccess;
};

#endif
