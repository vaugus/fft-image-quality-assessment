#include "gtest/gtest.h"
#include <sstream>
#include "../../include/handlers/quality_index.hpp"
#include "../../include/model/mask_lookup.hpp"
#include "../../include/wrappers/draw.hpp"
#include "../../include/wrappers/image_io.hpp"

extern ImageIO *io;

class QualityIndexTest : public ::testing::Test  {
  protected:
    virtual void SetUp() override {      
      handler = new QualityIndex(); 
    }

    QualityIndex *handler;
};

// TEST_F(QualityIndexTest, should_return_index_for_a_given_image) {
//   cv::Mat image = io->open_image("test/resources/squares.png");

//   double index = handler->compute_index(image);

//   EXPECT_EQ(765.27939090938582, index);
// }
