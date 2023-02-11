#include "../../include/handlers/binary_mask_handler.hpp"

BinaryMaskHandler::BinaryMaskHandler(Draw *draw) {
  this->draw = draw;
}

void BinaryMaskHandler::init_angle_functions_with_steps(int step, int limit) {
  for (int angle = 0; angle <= limit; angle += step) {
    this->cosines[angle] = cos(angle * M_PI / 180.0);
    this->sines[angle] = sin(angle * M_PI / 180.0);
    this->angles.emplace_back(angle);
  }
}

double BinaryMaskHandler::compute_vector_head(int x, int y, int angle) {
  return (x * y) / sqrt(pow((x * this->cosines[angle]), 2) + pow((y * this->sines[angle]), 2));
}

cv::Mat BinaryMaskHandler::create_radial_vector_mask(int width, int height) {
  const int center_width = width / 2;
  const int center_height = height / 2;

  cv::Point center = cv::Point(center_width, center_height);
  cv::Mat mask = draw->zeros(width, height, CV_8UC1);

  cv::Point vector_head;
  double radius_length = 0.0;

  for (auto angle : this->angles) {
    radius_length = compute_vector_head(center_height, center_width, angle);

    vector_head.x = (int) round(center.x + radius_length * this->cosines[angle]);
    vector_head.y = (int) round(center.y + radius_length * this->sines[angle]);

    draw->white_line(mask, center, vector_head);
  }

  mask.convertTo(mask, CV_8UC1);

  return mask;
}


std::string BinaryMaskHandler::handle(std::string request) {
  return AbstractHandler::handle(request);
}