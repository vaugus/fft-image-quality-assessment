#include <gtest/gtest.h>
#include <iostream>
#include "../../include/wrappers/draw.hpp"
#include "../../include/wrappers/fourier_transform.hpp"

extern Draw *draw;

const float  MAGNITUDE_ONE_32 = 1.4142135;
const float  LOG_ONE_32 = 0.69314718;
const double MAGNITUDE_ONE_64 = 1.414213562373095;
const double LOG_ONE_64 = 0.6931471805599453;

class MagnitudeTest : public ::testing::TestWithParam<std::tuple<cv::Mat, cv::Mat>> {
  protected:
    virtual void SetUp() override {      
      transform = new FourierTransform();
    }
  
    FourierTransform *transform;
};

TEST_P(MagnitudeTest, computes_magnitude_of_coefficients) {
  cv::Mat matrix = std::get<0>(GetParam());
  cv::Mat float_planes[] = { matrix, matrix };
  cv::Mat expected = std::get<1>(GetParam());

  cv::Mat actual = transform->magnitude(float_planes);

  EXPECT_NEAR(0, cv::norm(expected, actual, cv::NORM_L1), 1.0e-15);
}

INSTANTIATE_TEST_CASE_P(
  FourierTransformTest,
  MagnitudeTest,
  ::testing::Values(
    std::make_tuple(draw->zeros(2, 2, CV_32F), cv::Mat(2, 2, CV_32F, 0.0)),
    std::make_tuple(draw->zeros(2, 2, CV_64F), cv::Mat(2, 2, CV_64F, 0.0)),
    std::make_tuple(draw->ones(2, 2, CV_32F), cv::Mat(2, 2, CV_32F, MAGNITUDE_ONE_32)),
    std::make_tuple(draw->ones(2, 2, CV_64F), cv::Mat(2, 2, CV_64F, MAGNITUDE_ONE_64))));

class LogarithmicScaleTest : public ::testing::TestWithParam<std::tuple<cv::Mat, cv::Mat>> {
  protected:
    virtual void SetUp() override {      
      transform = new FourierTransform();
    }
  
    FourierTransform *transform;
};

TEST_P(LogarithmicScaleTest, computes_logarithmic_scale_of_coefficients) {
  cv::Mat spectrum = std::get<0>(GetParam());
  cv::Mat expected = std::get<1>(GetParam());

  cv::Mat actual = transform->logarithmic_scale(spectrum);

  EXPECT_NEAR(0, cv::norm(expected, actual, cv::NORM_L1), 1.0e-15);
}

INSTANTIATE_TEST_CASE_P(
  FourierTransformTest,
  LogarithmicScaleTest,
  ::testing::Values(
    std::make_tuple(draw->zeros(2, 2, CV_32F), cv::Mat(2, 2, CV_32F, 0.0)),
    std::make_tuple(draw->zeros(2, 2, CV_64F), cv::Mat(2, 2, CV_64F, 0.0)),
    std::make_tuple(draw->ones(2, 2, CV_32F), cv::Mat(2, 2, CV_32F, LOG_ONE_32)),
    std::make_tuple(draw->ones(2, 2, CV_64F), cv::Mat(2, 2, CV_64F, LOG_ONE_64))));

class FFTShiftTest : public ::testing::Test  {
  protected:
    virtual void SetUp() override {      
      transform = new FourierTransform();
    }
    
    void assert_quadrants_equals(cv::Mat quadrant, int value) {
      cv::Mat expected = cv::Mat(quadrant.size(), quadrant.type(), cv::Scalar(value));
      EXPECT_EQ(0, cv::norm(expected, quadrant, cv::NORM_L1));
    }
  
  FourierTransform *transform;
};

TEST_F(FFTShiftTest, shifts_quadrants_diagonally) {
  cv::Mat matrix = ( cv::Mat_<int>(4, 4) << 
    1, 1, 2, 2, 
    1, 1, 2, 2, 
    3, 3, 4, 4, 
    3, 3, 4, 4
  );

  Quadrants quadrants = transform->split_into_four_quadrants(matrix);
  assert_quadrants_equals(quadrants.top_left, 1);
  assert_quadrants_equals(quadrants.top_right, 2);
  assert_quadrants_equals(quadrants.bottom_left, 3);
  assert_quadrants_equals(quadrants.bottom_right, 4);

  cv::Mat shifted = transform->shift_quadrants(matrix);

  quadrants = {};
  quadrants = transform->split_into_four_quadrants(shifted);

  assert_quadrants_equals(quadrants.top_left, 4);
  assert_quadrants_equals(quadrants.top_right, 3);
  assert_quadrants_equals(quadrants.bottom_left, 2);
  assert_quadrants_equals(quadrants.bottom_right, 1);
}
