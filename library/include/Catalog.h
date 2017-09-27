#ifndef CATALOG_H
#define CATALOG_H

#include <string>
#include <vector>
#include <set>

class Holding;

class Catalog {
public:
    Catalog();
    virtual ~Catalog();

    static void deleteAll();

    unsigned int size() const;
    void add(Holding& holding);
    void update(Holding& holding);
    void findByClassification(const std::string&, std::set<Holding>& holdings) const;
    bool contains(const std::string&) const;
    Holding findByBarCode(const std::string&) const;
    static std::vector<Holding>* holdings();

private:
    Catalog(const Catalog&) = delete;

    static std::vector<Holding>* mHoldings;
};

#endif
