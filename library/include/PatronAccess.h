#ifndef PATRON_ACCESS_H
#define PATRON_ACCESS_H

#include <string>
#include <vector>

class Patron;

class PatronAccess
{
public:
    PatronAccess();
    virtual ~PatronAccess();

    void save(const Patron&);
    bool find(Patron&) const;
    Patron& findByName(const std::string&) const;
    int size() const;
    void update(const Patron&);
    std::vector<Patron> getAll() const;

    static void deleteAll();

private:
    PatronAccess& operator=(const PatronAccess&) = delete;
    PatronAccess(const PatronAccess&) = delete;

    std::vector<Patron>::iterator locate(const Patron&) const;
    std::vector<Patron>::iterator begin() const;
    std::vector<Patron>::iterator end() const;

    static std::vector<Patron>* mPatrons;
    static std::vector<Patron>* patrons();
};

#endif
