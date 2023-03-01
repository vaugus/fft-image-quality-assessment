#ifndef SPECTRUM_ANALYSIS_HPP
#define SPECTRUM_ANALYSIS_HPP

#include <vector>
#include "builder.hpp"
#include "mask_lookup.hpp"
#include "../../include/wrappers/fourier_transform.hpp"
#include "../../include/wrappers/image_io.hpp"
#include "../../include/wrappers/draw.hpp"

class SpectrumAnalysis : public Builder<SpectrumAnalysis> {
  private:
    double max;
    cv::Mat gray;
    cv::Mat spectrum;
    cv::Mat absolute_spectrum;
    std::vector<double> kurtosis_eligible_values;
    ComplexImage complex_image;
  public:
    SpectrumAnalysis& prepare_image(cv::Mat image);
    SpectrumAnalysis& apply_fft();
    SpectrumAnalysis& apply_mask();
    SpectrumAnalysis& compute_maximum_absolute_value();
    SpectrumAnalysis& filter_absolute_values_with_threshold(double threshold);

    ComplexImage get_complex_image();
    cv::Mat get_preprocessed_image();
    cv::Mat get_spectrum();
    cv::Mat get_absolute_spectrum();
    double get_max_absolute_value();
    std::vector<double> get_kurtosis_eligible_values();
};

#endif
