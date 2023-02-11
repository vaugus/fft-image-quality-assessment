#include "../../include/wrappers/draw.hpp"

cv::Mat Draw::zeros(int width, int height, int type) {
  return cv::Mat::zeros(height, width, type);
}

void Draw::draw_line(cv::Mat image, cv::Point center, cv::Point head, cv::Scalar color, int line_type, int shift) {
  cv::line(image, center, head, color, line_type, shift);
}

void Draw::white_line(cv::Mat image, cv::Point center, cv::Point head) {
  draw_line(image, center, head, this->WHITE, 1, 16);
}

void Draw::draw_elipse(cv::Mat image, cv::Point center, double angle) {
  int thickness = 2;
  int line_type = 8;
  int width = image.rows;

  ellipse(image,
          center,
          cv::Size(width / 4, width / 16),
          angle,
          0,
          360,
          cv::Scalar(255, 0, 0),
          thickness,
          line_type);
}

void Draw::draw_filled_circle(cv::Mat image, cv::Point center) {
  int width = image.rows;

  circle(image,
         center,
         width / 32,
         cv::Scalar(0, 0, 255),
         cv::FILLED,
         cv::LINE_8);
}

cv::Mat Draw::create_atom_image() {
  int width = 400;
  cv::Mat atom = cv::Mat::zeros(width, width, CV_8UC3);
  cv::Point center = cv::Point(width / 2, width / 2);

  auto elipse = [this, atom, center](double angle) {
    draw_elipse(atom, center, angle);
  };

  elipse(90);
  elipse(0);
  elipse(45);
  elipse(-45);

  draw_filled_circle(atom, center);

  return atom;
}