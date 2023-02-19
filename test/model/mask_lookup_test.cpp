#include "gtest/gtest.h"
#include <sstream>
#include "../../include/model/mask_lookup.hpp"
#include "../../include/wrappers/draw.hpp"

MaskLookup *lookup = MaskLookup::get_instance();
extern Draw *draw;

TEST(MaskLookupTest, initializes_with_empty_map) {
  EXPECT_TRUE(lookup->of(100, 100).empty());
  EXPECT_FALSE(lookup->mask_exists(100, 100));
}

TEST(MaskLookupTest, should_insert_and_return_masks) {
  cv::Mat zeros = draw->zeros(100, 200, CV_8UC1);

  lookup->insert(zeros);

  cv::Mat cached_mask = lookup->of(100, 200);
  EXPECT_EQ(100, cached_mask.cols);
  EXPECT_EQ(200, cached_mask.rows);
  EXPECT_EQ(0, cv::norm(zeros, cached_mask, cv::NORM_L1));
}
