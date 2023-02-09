#include "gtest/gtest.h"
#include <string>
#include <iostream>
#include <iomanip>

#include "../include/binary_mask_handler.hpp"

class BinaryMaskHandlerTest : public ::testing::Test  {
  protected:
    virtual void SetUp() override {      
      handler = new BinaryMaskHandler(); 
    }

    double round(double value) {
      std::stringstream valueString;
      valueString << std::setprecision(6) << std::fixed << value;
      return std::stod(valueString.str());
    }

    BinaryMaskHandler *handler;
};

TEST_F(BinaryMaskHandlerTest, initializes_angle_data_with_empty_array) {
  EXPECT_EQ(handler->sines.size(), 0);
  EXPECT_EQ(handler->cosines.size(), 0);
}

// theta = {0, 15, 30, 45, 60, 75, 90}
TEST_F(BinaryMaskHandlerTest, fills_angle_data) {
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
