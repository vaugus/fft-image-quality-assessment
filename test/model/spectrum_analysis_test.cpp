#include "gtest/gtest.h"

#include "../../include/util.hpp"
#include "../../include/model/spectrum_analysis.hpp"
#include "../../include/model/mask_lookup.hpp"
#include "../../include/wrappers/draw.hpp"
#include "../../include/wrappers/image_io.hpp"

extern Draw *draw;
extern ImageIO *io;
extern MaskLookup *lookup;

class SpectrumAnalysisTest : public ::testing::Test  {
  protected:
    virtual void SetUp() override {      
      image = io->open_image("test/resources/squares.png");
    }

    cv::Mat image;
};

TEST_F(SpectrumAnalysisTest, prepares_grayscale_image_for_fourier_transform) {
  SpectrumAnalysis analysis = SpectrumAnalysis::builder()
    .prepare_image(image)
    .build();

  cv::Mat gray = analysis.get_preprocessed_image();

  EXPECT_EQ(CV_8UC3, image.type());
  EXPECT_FALSE(gray.empty());
  EXPECT_EQ(CV_8UC1, gray.type());
  EXPECT_EQ(image.rows, gray.rows);
  EXPECT_EQ(image.cols, gray.cols);
}

TEST_F(SpectrumAnalysisTest, performs_the_fourier_transform_of_grayscale_image) {
  SpectrumAnalysis analysis = SpectrumAnalysis::builder()
    .prepare_image(image)
    .apply_fft()
    .build();

  EXPECT_FALSE(analysis.get_complex_image().real.empty());
  EXPECT_FALSE(analysis.get_complex_image().imaginary.empty());
  EXPECT_FALSE(analysis.get_spectrum().empty());
  EXPECT_EQ(CV_64F, analysis.get_spectrum().type());
  EXPECT_EQ(image.rows, analysis.get_spectrum().rows);
  EXPECT_EQ(image.cols, analysis.get_spectrum().cols);
}

TEST_F(SpectrumAnalysisTest, computes_absolute_values_and_its_maximum) {
  cv::Mat mask = io->grayscale(io->open_image("test/resources/100-100.png"));
  lookup->insert(mask);

  SpectrumAnalysis analysis = SpectrumAnalysis::builder()
    .prepare_image(image)
    .apply_fft()
    .apply_mask()
    .compute_maximum_absolute_value()
    .build();

  cv::Mat expected = io->read_from_yaml("test/resources/yaml/absolute-spectrum.yaml");
  EXPECT_EQ(426974, analysis.get_max_absolute_value());
}

TEST_F(SpectrumAnalysisTest, filters_pixels_given_a_threshold) {
  cv::Mat mask = io->grayscale(io->open_image("test/resources/100-100.png"));
  lookup->insert(mask);

  SpectrumAnalysis analysis = SpectrumAnalysis::builder()
    .prepare_image(image)
    .apply_fft()
    .apply_mask()
    .compute_maximum_absolute_value()
    .filter_absolute_values_with_threshold(1000.0)
    .build();

  std::vector<double> values = analysis.get_kurtosis_eligible_values();
  std::vector<double> expected = util::read_doubles_from_file("test/resources/txt/values.txt");

  int size = values.size();

  EXPECT_EQ(expected.size(), size);

  for (int i = 0; i < size; i++) {
    EXPECT_NEAR(expected.at(i), values.at(i), 0.01);
  }
}
