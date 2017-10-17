#ifndef HOLDING_SERVICE_H
#define HOLDING_SERVICE_H

#include "PatronService.h"
#include "BranchService.h"
#include "Catalog.h"
#include "Holding.h"

#include "boost/date_time/gregorian/gregorian_types.hpp"

#include <vector>
#include <set>

class Branch;
class Patron;

namespace service {
    class HoldingService {
    public:
        HoldingService();
        virtual ~HoldingService();

        static void deleteAll();

        virtual void addAtBranch(const std::string& branchId, const std::string& barcode);
        virtual void checkIn(const std::string& barCode, boost::gregorian::date, const std::string& branchId);
        virtual void checkOut(const std::string& patronCardNumber, const std::string& barCode, boost::gregorian::date);
        void transfer(Holding&, Branch&);
        void transfer(const std::string& barCode, const std::string& branchId);

        unsigned int inventorySize() const;
        virtual bool existsWithBarcode(const std::string& barCode) const;
        virtual bool isAvailable(const std::string& barCode) const;
        Holding findByBarCode(const std::string&) const;
        void findByClassification(const std::string& classification, std::set<Holding>& holdings) const;

    private:
        HoldingService(const HoldingService&) = delete;
        HoldingService& operator=(const HoldingService&) = delete;

        PatronService mPatronService;
        BranchService mBranchService;
        Catalog mCatalog;
    };
}

#endif
