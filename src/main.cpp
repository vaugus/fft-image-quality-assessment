#include "gtest/gtest.h"
#include <iostream>

int main(int argc, char **argv) {
  if (strcmp(argv[1], "test") == 0) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }

  return 0;
}