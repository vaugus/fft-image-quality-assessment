#include "../../include/handlers/binary_mask.hpp"
#include "../../include/model/mask_lookup.hpp"

extern Draw *draw;

void BinaryMask::init_angle_functions_with_steps(int step, int limit) {
  for (int angle = 0; angle <= limit; angle += step) {
    this->cosines[angle] = cos(angle * M_PI / 180.0);
    this->sines[angle] = sin(angle * M_PI / 180.0);
    this->angles.emplace_back(angle);
  }
}

double BinaryMask::compute_vector_head(int x, int y, int angle) {
  return (x * y) / sqrt(pow((x * this->cosines[angle]), 2) + pow((y * this->sines[angle]), 2));
}

cv::Mat BinaryMask::create_radial_vector_mask(int width, int height) {
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

  return mask;
}

Request BinaryMask::handle(Request request) {
  MaskLookup *lookup = MaskLookup::get_instance();
  cv::Mat image = request.image;
  this->init_angle_functions_with_steps(5, 360);

  if (lookup->mask_exists(image.rows, image.cols))
    return AbstractHandler::handle(request);
  
  cv::Mat mask = create_radial_vector_mask(image.rows, image.cols);
  lookup->insert(mask);

  return AbstractHandler::handle(request);
}