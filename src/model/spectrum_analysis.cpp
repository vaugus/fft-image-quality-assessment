#include "../../include/model/spectrum_analysis.hpp"
#include <iostream>

extern Draw *draw;
extern ImageIO *io;
FourierTransform *fft = new FourierTransform();
extern MaskLookup *lookup;

SpectrumAnalysis& SpectrumAnalysis::prepare_image(cv::Mat image) {
  gray = draw->pad_with_zeros(io->grayscale(image));
  return *this;
}

SpectrumAnalysis& SpectrumAnalysis::apply_fft() {
  complex_image = fft->perform_fft(gray);
  spectrum = fft->shift_quadrants(
              fft->logarithmic_scale(
                fft->compute_magnitude(complex_image)));

  return *this;
}

SpectrumAnalysis& SpectrumAnalysis::apply_mask() {
  cv::Mat mask = lookup->of(spectrum.rows, spectrum.cols);
  mask.convertTo(mask, spectrum.type(), 1.0 / 255.0);
  spectrum = spectrum.mul(mask);

  return *this;
}

SpectrumAnalysis& SpectrumAnalysis::compute_maximum_absolute_value() {
  spectrum_abs_values = cv::abs(spectrum);

  double min; 
  cv::minMaxLoc(spectrum_abs_values, &min, &this->max);
  return *this;
}
