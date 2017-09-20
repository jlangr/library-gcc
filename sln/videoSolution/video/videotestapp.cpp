#include <iostream>
#include "gtest/gtest.h"

using namespace testing;

int main(int argc, char** argv) {
    InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    std::getchar();
}
