#include <fstream>
#include <gtest/gtest.h>
#include "../../include/wrappers/image_io.hpp"

#include <iostream>

extern Draw *draw;
ImageIO *io = new ImageIO(draw);

TEST(open_image, should_return_cv_mat_with_pixels) {
  cv::Mat image = io->open_image("test/resources/atom.png");
  EXPECT_EQ(0, cv::norm(image, draw->create_atom_image(), cv::NORM_L1));
}

TEST(save_image, should_save_png_file) {
  std::string path = "test/resources/save_image_test.png";
  cv::Mat image(300, 300, CV_8UC3, cv::Scalar(0,0, 100));
  EXPECT_FALSE(image.empty());
  EXPECT_TRUE(io->save_image(path, image));

  cv::Mat saved_image = io->open_image(path);
  EXPECT_EQ(0, cv::norm(image, saved_image, cv::NORM_L1));

  std::remove(path.c_str());
  EXPECT_FALSE(std::ifstream(path));
}

TEST(grayscale, should_convert_three_channels_to_one_channel) {
  cv::Mat image = io->open_image("test/resources/squares.png");

  cv::Mat grayscale = io->grayscale(image);

  EXPECT_EQ(3, image.channels());
  EXPECT_EQ(1, grayscale.channels());
}

TEST(yaml_io, saves_mat_as_yaml_and_reads_it) {
  std::string path = "test/resources/yaml/save-yaml-test.yaml";
  cv::Mat image = io->grayscale(io->open_image("test/resources/squares.png"));
  io->save_as_yaml(path, image);

  cv::Mat saved_image = io->read_from_yaml(path);
  EXPECT_EQ(0, cv::norm(image, saved_image, cv::NORM_L1));
  std::remove(path.c_str());
}
