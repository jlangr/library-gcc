project(libraryTest)
cmake_minimum_required(VERSION 3.7)

include_directories(../googletest/googlemock/include ../googletest/googletest/include ../boost ../library/include)
link_directories(../googletest/googlemock ../googletest/googlemock/gtest ../library ../ftplibpp)
add_definitions(-std=c++11)

set(sources 
   main.cpp 
   BarcodeUtilTest.cpp
   BookTest.cpp
   BranchAccessTest.cpp
   BranchServiceTest.cpp
   BranchTest.cpp
   CatalogTest.cpp
   ClassificationServiceTest.cpp
   CustomerTest.cpp
   ExamplesTest.cpp
   HoldingBarcodeTest.cpp
   HoldingServiceTest.cpp
   HoldingTest.cpp
   InventoryReportTest.cpp
   KeyedFilePersistenceTest.cpp
   KeyedMemoryPersistenceTest.cpp
   NameNormalizerTest.cpp
   PatronAccessTest.cpp
   PatronServiceTest.cpp
   PatronTest.cpp
   PersistenceTest.cpp
   ReportMailerTest.cpp
   ScannerStateCheckinTest.cpp
   ScannerStateCheckoutTest.cpp
   ScannerStateInventoryTest.cpp
   ScannerStateWaitingTest.cpp
   ScannerTestData.cpp
   StreamLineReaderTest.cpp
   TimestampSourceTest.cpp
   VectorReaderTest.cpp
   )
add_executable(libraryTest ${sources})
target_link_libraries(libraryTest pthread)
target_link_libraries(libraryTest gmock)
target_link_libraries(libraryTest gtest)
target_link_libraries(libraryTest rt)
target_link_libraries(libraryTest library)
target_link_libraries(libraryTest ftp++)

