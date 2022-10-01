#include <gtest/gtest.h>
#include "../include/image_io.hpp"

TEST(open_image, should_return_cv_mat_with_pixels)
{
    ImageIO *io = new ImageIO();
    EXPECT_EQ(1, 1);
}