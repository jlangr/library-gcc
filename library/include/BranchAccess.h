#ifndef BRANCH_ACCESS_H
#define BRANCH_ACCESS_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>

#include "Persistence.h"

class Branch;

class BranchAccess
{
public:
    BranchAccess();
    explicit BranchAccess(std::shared_ptr<Persistence<Branch>> persister);
    virtual ~BranchAccess();

    static std::string dataFileName();

    bool find(Branch&) const;
    int size() const;
    bool existsWithName(const std::string& name) const;
    void save(const Branch&);
    void deleteAll();

private:
    std::shared_ptr<Persistence<Branch>> mPersister;
};

#endif
