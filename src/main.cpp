#include "gtest/gtest.h"
#include <iostream>
#include "../include/wrappers/draw.hpp"
#include "../include/wrappers/image_io.hpp"
#include "../include/wrappers/statistics.hpp"
#include "../include/model/mask_lookup.hpp"

Draw *draw;
ImageIO *io;
MaskLookup *lookup;
Statistics *statistics;

int main(int argc, char **argv) {
  draw = new Draw();
  io = new ImageIO(draw);
  lookup = MaskLookup::get_instance();
  statistics = new Statistics();

  if (strcmp(argv[1], "test") == 0) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }

  return 0;
}