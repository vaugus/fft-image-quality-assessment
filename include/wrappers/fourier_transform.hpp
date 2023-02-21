#ifndef FOURIER_TRANSFORM_HPP
#define FOURIER_TRANSFORM_HPP

#include "opencv4/opencv2/core.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/imgcodecs.hpp"
#include "opencv4/opencv2/highgui.hpp"

struct Quadrants {
  cv::Mat top_left;
  cv::Mat top_right;
  cv::Mat bottom_left;
  cv::Mat bottom_right;
};

class FourierTransform {
  public:
    cv::Mat perform_fft(cv::Mat image);
    cv::Mat magnitude(cv::Mat *complex_planes);
    cv::Mat logarithmic_scale(cv::Mat magnitude);
    Quadrants split_into_four_quadrants(cv::Mat matrix);
    cv::Mat merge_quadrants(Quadrants quadrants, cv::Mat initial_image);
    cv::Mat shift_quadrants(cv::Mat spectrum);
};

#endif