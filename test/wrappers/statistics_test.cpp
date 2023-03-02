#include <gtest/gtest.h>
#include "../../include/wrappers/statistics.hpp"

std::vector<double> integers = { 10.0, 20.0, 30.0 };
std::vector<double> floating = { 3.14, 16.213, 6.2342095832 };

class MeanTest : public ::testing::TestWithParam<std::tuple<std::vector<double>, double>> {
  protected:
    virtual void SetUp() override {      
      wrapper = new Statistics(); 
    }
  
    Statistics *wrapper;
};

TEST_P(MeanTest, should_calculate_mean_value_among_vector_of_doubles) {
  EXPECT_EQ(std::get<1>(GetParam()), wrapper->mean(std::get<0>(GetParam())));
}

INSTANTIATE_TEST_CASE_P(
  StatisticsTest,
  MeanTest,
  ::testing::Values(
      std::make_tuple(integers, 20),
      std::make_tuple(floating, 8.5290698610666666)));

class MomentTest : public ::testing::TestWithParam<std::tuple<std::vector<double>, double>> {
  protected:
    virtual void SetUp() override {      
      wrapper = new Statistics(); 
    }
  
    Statistics *wrapper;
};

TEST_P(MomentTest, should_calculate_moment_value_among_vector_of_doubles) {
  EXPECT_EQ(std::get<1>(GetParam()), wrapper->moment(std::get<0>(GetParam()), 4));
}

INSTANTIATE_TEST_CASE_P(
  StatisticsTest,
  MomentTest,
  ::testing::Values(
      std::make_tuple(integers, 6666.666666666667),
      std::make_tuple(floating, 1452.409002908822)));


class KurtosisTest : public ::testing::TestWithParam<std::tuple<std::vector<double>, double>> {
  protected:
    virtual void SetUp() override {      
      wrapper = new Statistics(); 
    }
  
    Statistics *wrapper;
};

TEST_P(KurtosisTest, should_calculate_kurtosis_value_among_vector_of_doubles) {
  EXPECT_EQ(std::get<1>(GetParam()), wrapper->kurtosis(std::get<0>(GetParam())));
}

INSTANTIATE_TEST_CASE_P(
  StatisticsTest,
  KurtosisTest,
  ::testing::Values(
      std::make_tuple(integers, -1.5000000000000002),
      std::make_tuple(floating, -1.4999999999999996)));
