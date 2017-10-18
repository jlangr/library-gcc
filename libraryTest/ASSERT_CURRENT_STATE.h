#ifndef ASSERT_CURRENT_STATE_H
#define ASSERT_CURRENT_STATE_H

#include "Scanner.h"

template <typename T> static void ASSERT_CURRENT_STATE(Scanner& scanner) {
    ASSERT_TRUE(dynamic_cast<T*>(scanner.currentState()) != NULL);
}

#endif
