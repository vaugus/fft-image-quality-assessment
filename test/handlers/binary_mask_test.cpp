#include "gtest/gtest.h"
#include <sstream>
#include "../../include/handlers/binary_mask.hpp"
#include "../../include/model/mask_lookup.hpp"
#include "../../include/wrappers/draw.hpp"
#include "../../include/wrappers/image_io.hpp"

Draw *draw = new Draw();
extern ImageIO *io;

class BinaryMaskTest : public ::testing::Test  {
  protected:
    virtual void SetUp() override {      
      handler = new BinaryMask(draw); 
    }

    double round(double value) {
      std::stringstream valueString;
      valueString << std::setprecision(6) << std::fixed << value;
      return std::stod(valueString.str());
    }

    BinaryMask *handler;
};

TEST_F(BinaryMaskTest, initializes_angle_data_with_empty_array) {
  EXPECT_EQ(handler->sines.size(), 0);
  EXPECT_EQ(handler->cosines.size(), 0);
}

// theta = {0, 15, 30, 45, 60, 75, 90}
TEST_F(BinaryMaskTest, fills_angle_data) {
  handler->init_angle_functions_with_steps(15, 90);

  EXPECT_EQ(round(handler->sines[0]), 0.0);
  EXPECT_EQ(round(handler->sines[15]), 0.258819);
  EXPECT_EQ(round(handler->sines[30]), 0.5);
  EXPECT_EQ(round(handler->sines[45]), 0.707107);
  EXPECT_EQ(round(handler->sines[60]), 0.866025);
  EXPECT_EQ(round(handler->sines[75]), 0.965926);
  EXPECT_EQ(round(handler->sines[90]), 1.0);

  EXPECT_EQ(round(handler->cosines[90]), 0.0);
  EXPECT_EQ(round(handler->cosines[75]), 0.258819);
  EXPECT_EQ(round(handler->cosines[60]), 0.5);
  EXPECT_EQ(round(handler->cosines[45]), 0.707107);
  EXPECT_EQ(round(handler->cosines[30]), 0.866025);
  EXPECT_EQ(round(handler->cosines[15]), 0.965926);
  EXPECT_EQ(round(handler->cosines[0]), 1.0);
}

TEST_F(BinaryMaskTest, creates_new_mask_if_not_exists) {
  MaskLookup *lookup = MaskLookup::get_instance();
  cv::Mat image = draw->zeros(400, 200, CV_8UC1);
  Request request;
  request.image = image;
  int initial_size = lookup->size();

  EXPECT_TRUE(lookup->of(image.rows, image.cols).empty());
  handler->handle(request);

  EXPECT_FALSE(lookup->of(image.rows, image.cols).empty());
  EXPECT_EQ(initial_size + 1, lookup->size());
  handler->handle(request);

  EXPECT_EQ(initial_size + 1, lookup->size());
}

class CreateRadialVectorMaskTest : public ::testing::TestWithParam<std::tuple<int, int>> {
  protected:
    virtual void SetUp() override {      
      handler = new BinaryMask(draw); 
    }
  
    BinaryMask *handler;
};

TEST_P(CreateRadialVectorMaskTest, should_create_mask_with_given_parameters) {
  handler->init_angle_functions_with_steps(5, 360);

  int width = std::get<1>(GetParam());
  int height = std::get<0>(GetParam());
  
  cv::Mat mask = handler->create_radial_vector_mask(width, height);

  EXPECT_FALSE(mask.empty());
  EXPECT_EQ(mask.rows, height);
  EXPECT_EQ(mask.cols, width);

  std::stringstream file_name;
  file_name << "test/resources/" << width << "-" << height << ".png";

  cv::Mat mask_template = io->open_image(file_name.str());
  mask_template.convertTo(mask_template, CV_8U);
  cv::cvtColor(mask_template, mask_template, cv::COLOR_BGR2GRAY);

  EXPECT_EQ(0, cv::norm(mask, mask_template, cv::NORM_L1));
}

INSTANTIATE_TEST_CASE_P(
  BinaryMaskTest,
  CreateRadialVectorMaskTest,
  ::testing::Values(
      std::make_tuple(100, 100),
      std::make_tuple(100, 200),
      std::make_tuple(200, 100)));
