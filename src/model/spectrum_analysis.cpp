#include "../../include/model/spectrum_analysis.hpp"

extern Draw *draw;
extern ImageIO *io;
FourierTransform *fft = new FourierTransform();
extern MaskLookup *lookup;

SpectrumAnalysis& SpectrumAnalysis::prepare_image(cv::Mat image) {
  this->gray = draw->pad_with_zeros(io->grayscale(image));
  return *this;
}

SpectrumAnalysis& SpectrumAnalysis::apply_fft() {
  this->complex_image = fft->perform_fft(gray);
  this->spectrum = fft->shift_quadrants(fft->compute_magnitude(complex_image));
  return *this;
}

SpectrumAnalysis& SpectrumAnalysis::apply_mask() {
  cv::Mat mask = lookup->of(spectrum.rows, spectrum.cols);
  mask.convertTo(mask, spectrum.type(), 1.0 / 255.0);
  this->spectrum = spectrum.mul(mask);

  return *this;
}

SpectrumAnalysis& SpectrumAnalysis::compute_maximum_absolute_value() {
  this->absolute_spectrum = cv::abs(this->spectrum);

  double min; 
  cv::minMaxLoc(this->absolute_spectrum, &min, &this->max);
  return *this;
}

ComplexImage SpectrumAnalysis::get_complex_image() {
  return this->complex_image;
}

cv::Mat SpectrumAnalysis::get_preprocessed_image() {
  return this->gray;
}

cv::Mat SpectrumAnalysis::get_spectrum() {
  return this->spectrum;
}

cv::Mat SpectrumAnalysis::get_absolute_spectrum() {
  return this->absolute_spectrum;
}

double SpectrumAnalysis::get_max_absolute_value() {
  return this->max;
}
