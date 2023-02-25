#include "../../include/wrappers/fourier_transform.hpp"

ComplexImage FourierTransform::perform_fft(cv::Mat image) {
  cv::Mat spectrum;
  cv::Mat complex_planes[] = {
    cv::Mat_<double>(image),
    cv::Mat::zeros(image.size(), CV_64F)
  };

  // Add a third plane with zeros to the complex planes and perform fft.
  cv::merge(complex_planes, 2, spectrum);
  cv::dft(spectrum, spectrum);

  // complex_planes[0] = Re(DFT(I), complex_planes[1] = Im(DFT(I))
  cv::split(spectrum, complex_planes);

  ComplexImage complex_image = { complex_planes[0], complex_planes[1]};

  return complex_image;
}

cv::Mat FourierTransform::compute_magnitude(ComplexImage image) {
  cv::magnitude(image.real, image.real, image.imaginary);
  return image.real;
}

cv::Mat FourierTransform::logarithmic_scale(cv::Mat spectrum) {
  spectrum += cv::Scalar::all(1);
  log(spectrum, spectrum);
  return spectrum;
}

Quadrants FourierTransform::split_into_four_quadrants(cv::Mat matrix) {
  int x = matrix.cols / 2;
  int y = matrix.rows / 2;

  Quadrants quadrants = {};

  matrix(cv::Rect(0, 0, x, y)).copyTo(quadrants.top_left);
  matrix(cv::Rect(x, 0, x, y)).copyTo(quadrants.top_right);
  matrix(cv::Rect(0, y, x, y)).copyTo(quadrants.bottom_left);
  matrix(cv::Rect(x, y, x, y)).copyTo(quadrants.bottom_right);

  return quadrants;
}

cv::Mat FourierTransform::merge_quadrants(Quadrants quadrants, cv::Mat initial_image) {
  cv::Mat new_image = cv::Mat(initial_image.size(), initial_image.type());

  int x = initial_image.cols / 2;
  int y = initial_image.rows / 2;

  quadrants.top_left.copyTo(new_image.colRange(0, x).rowRange(0, y));
  quadrants.top_right.copyTo(new_image.colRange(x, initial_image.cols).rowRange(0, y));
  quadrants.bottom_left.copyTo(new_image.colRange(0, x).rowRange(y, initial_image.rows));
  quadrants.bottom_right.copyTo(new_image.colRange(x, initial_image.cols).rowRange(y, initial_image.rows));

  return new_image;
}

cv::Mat FourierTransform::shift_quadrants(cv::Mat spectrum) {
  Quadrants quadrants = split_into_four_quadrants(spectrum);

  cv::Mat temporary_image;

  // swap quadrants (top-left with bottom-right)
  quadrants.top_left.copyTo(temporary_image);
  quadrants.bottom_right.copyTo(quadrants.top_left);
  temporary_image.copyTo(quadrants.bottom_right);

  // swap quadrant (top-right with bottom-left)
  quadrants.top_right.copyTo(temporary_image);                    
  quadrants.bottom_left.copyTo(quadrants.top_right);
  temporary_image.copyTo(quadrants.bottom_left);

  temporary_image.release();

  return merge_quadrants(quadrants, spectrum);
}
