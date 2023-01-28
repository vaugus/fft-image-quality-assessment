#include <fstream>
#include <gtest/gtest.h>
#include "opencv2/highgui/highgui.hpp"
#include "../include/image_io.hpp"
#include "../include/test_utils.hpp"

TestUtils *utils = new TestUtils();
ImageIO *io = new ImageIO();

TEST(open_image, should_return_cv_mat_with_pixels) {
  cv::Mat image = io->open_image("test/resources/atom.png");

  EXPECT_EQ(0, cv::norm(image, utils->create_atom_image(), cv::NORM_L1));
}

TEST(save_image, should_save_png_file) {
  ImageIO *io = new ImageIO();
  cv::Mat image(300, 300, CV_8UC3, cv::Scalar(0,0, 100));
  EXPECT_FALSE(image.empty());
  EXPECT_TRUE(io->save_image("test/resources/save_image_test.png", image));

  cv::Mat saved_image = io->open_image("test/resources/save_image_test.png");
  EXPECT_EQ(0, cv::norm(image, saved_image, cv::NORM_L1));

  std::remove("test/resources/save_image_test.png");
  EXPECT_FALSE(std::ifstream("test/resources/save_image_test.png"));
}