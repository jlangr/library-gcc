project(library)
cmake_minimum_required(VERSION 2.7)

include_directories(../boost ./include)
add_definitions(-std=c++0x)

set(sources 
   include/BarcodeUtil.h
   Book.cpp
   Branch.cpp
   BranchAccess.cpp
   BranchService.cpp
   Catalog.cpp
   ClassificationService.cpp
   Customer.cpp
   Endpoint.cpp
   EndpointValidator.cpp
   Holding.cpp
   HoldingService.cpp
   InventoryReport.cpp
   MailDestination.cpp
   MailMessage.cpp
   Movie.cpp
   include/NameNormalizer.h
   Patron.cpp
   PatronAccess.cpp
   PatronService.cpp
   Rental.cpp
   Scanner.cpp
   ScannerState.cpp
   ScannerStateCheckin.cpp
   ScannerStateCheckout.cpp
   ScannerStateInventory.cpp
   ScannerStateWaiting.cpp
   Soundex.cpp
   StreamLineReader.cpp
   TimestampSource.cpp
   Transport.cpp
   )
add_library(library ${sources})
target_link_libraries(library pthread)
target_link_libraries(library rt)

