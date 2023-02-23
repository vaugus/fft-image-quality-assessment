#ifndef DRAW_HPP
#define DRAW_HPP

#include "opencv4/opencv2/core.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/imgcodecs.hpp"
#include "opencv4/opencv2/highgui.hpp"

struct Border {
  int top;
  int bottom;
  int left;
  int right;
  int type;
  cv::Scalar value;
};

class Draw {
  private:
    void draw_line(cv::Mat image, cv::Point center, cv::Point head, cv::Scalar color, int line_type, int shift);

  public:
    static const cv::Scalar ZERO_BGR;
    static const cv::Scalar ONE_BGR;

    cv::Mat apply_border(cv::Mat source, Border border);
    Border create_zeros_square_border(cv::Mat image);

    cv::Mat zeros(int width, int height, int type);
    cv::Mat ones(int width, int height, int type);
    void white_line(cv::Mat image, cv::Point center, cv::Point head);

    void draw_elipse(cv::Mat image, cv::Point center, double angle);
    void draw_filled_circle(cv::Mat image, cv::Point center);
    cv::Mat create_atom_image();

    cv::Mat pad_with_zeros(cv::Mat image);
};

#endif