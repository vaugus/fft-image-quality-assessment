#include <fstream>
#include <gtest/gtest.h>
#include "../../include/wrappers/image_io.hpp"

extern Draw *draw;
ImageIO *io = new ImageIO(draw);

TEST(open_image, should_return_cv_mat_with_pixels) {
  cv::Mat image = io->open_image("test/resources/atom.png");

  EXPECT_EQ(0, cv::norm(image, draw->create_atom_image(), cv::NORM_L1));
}

TEST(save_image, should_save_png_file) {
  cv::Mat image(300, 300, CV_8UC3, cv::Scalar(0,0, 100));
  EXPECT_FALSE(image.empty());
  EXPECT_TRUE(io->save_image("test/resources/save_image_test.png", image));

  cv::Mat saved_image = io->open_image("test/resources/save_image_test.png");
  EXPECT_EQ(0, cv::norm(image, saved_image, cv::NORM_L1));

  std::remove("test/resources/save_image_test.png");
  EXPECT_FALSE(std::ifstream("test/resources/save_image_test.png"));
}

TEST(grayscale, should_convert_three_channels_to_one_channel) {
  cv::Mat image = io->open_image("test/resources/squares.png");

  cv::Mat grayscale = io->grayscale(image);

  EXPECT_EQ(3, image.channels());
  EXPECT_EQ(1, grayscale.channels());
}