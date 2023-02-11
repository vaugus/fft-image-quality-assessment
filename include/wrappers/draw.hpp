#ifndef DRAW_HPP
#define DRAW_HPP

#include "opencv4/opencv2/core.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/imgcodecs.hpp"
#include "opencv4/opencv2/highgui.hpp"

class Draw {
  private:
    const cv::Scalar WHITE = cv::Scalar(255, 255, 255);
    void draw_line(cv::Mat image, cv::Point center, cv::Point head, cv::Scalar color, int line_type, int shift);

  public:
    cv::Mat zeros(int width, int height, int type);
    void white_line(cv::Mat image, cv::Point center, cv::Point head);

    void draw_elipse(cv::Mat image, cv::Point center, double angle);
    void draw_filled_circle(cv::Mat image, cv::Point center);
    cv::Mat create_atom_image();
};

#endif