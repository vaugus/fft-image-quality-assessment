#include <gtest/gtest.h>
#include "../include/image_io.hpp"
#include "../include/test_utils.hpp"

TestUtils *utils = new TestUtils();

TEST(open_image, should_return_cv_mat_with_pixels) {
    ImageIO *io = new ImageIO();
    cv::Mat image = io->open_image("test/resources/atom.png");

    EXPECT_EQ(0, cv::norm(image, utils->create_atom_image(), cv::NORM_L1));
}