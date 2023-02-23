#include <gtest/gtest.h>
#include "../../include/wrappers/draw.hpp"

extern Draw *draw;

TEST(create_zeros_square_border, creates_empty_border_if_image_is_square) {
  cv::Mat image = draw->zeros(32, 32, CV_8U);

  Border border = draw->create_zeros_square_border(image);

  EXPECT_EQ(0, border.top);
  EXPECT_EQ(0, border.bottom);
  EXPECT_EQ(0, border.left);
  EXPECT_EQ(0, border.right);
  EXPECT_EQ(cv::BORDER_CONSTANT, border.type);
  EXPECT_EQ(Draw::ZERO_BGR, border.value);
}

TEST(create_zeros_square_border, creates_border_if_image_is_not_square) {
  cv::Mat image = draw->zeros(64, 128, CV_8U);

  Border border = draw->create_zeros_square_border(image);

  EXPECT_EQ(0, border.top);
  EXPECT_EQ(0, border.bottom);
  EXPECT_EQ(0, border.left);
  EXPECT_EQ(64, border.right);
  EXPECT_EQ(cv::BORDER_CONSTANT, border.type);
  EXPECT_EQ(Draw::ZERO_BGR, border.value);
}

TEST(apply_border, does_not_change_the_image_with_empty_border) {
  cv::Mat image = draw->zeros(32, 32, CV_8U);

  cv::Mat target = draw->apply_border(image, draw->create_zeros_square_border(image));

  EXPECT_EQ(0, cv::norm(image, target, cv::NORM_L1));
}

TEST(apply_border, applies_non_empty_border_to_image) {
  cv::Mat image = draw->ones(32, 64, CV_8U);

  cv::Mat target = draw->apply_border(image, draw->create_zeros_square_border(image));
  cv::Mat ones_region = target(cv::Range(0, 64), cv::Range(0, 32));
  cv::Mat zeros_region = target(cv::Range(0, 64), cv::Range(32, 64));

  EXPECT_EQ(64, target.rows);
  EXPECT_EQ(64, target.cols);
  EXPECT_EQ(0, cv::norm(ones_region, image, cv::NORM_L1));
  EXPECT_EQ(0, cv::norm(zeros_region, draw->zeros(32, 64, CV_8U), cv::NORM_L1));
}
