#include "UnitTestHarness/CommandLineTestRunner.h"

int main(int argc, char** argv) {
	CommandLineTestRunner::RunAllTests(argc, argv);
	return 0;
}

IMPORT_TEST_GROUP(Customer); 
IMPORT_TEST_GROUP(Rental); 
IMPORT_TEST_GROUP(Movie); 
