#include "../../include/wrappers/image_io.hpp"

ImageIO::ImageIO(Draw *draw) {
  this->draw = draw;
}

cv::Mat ImageIO::open_image(std::string const& path) {
  return cv::imread(path);
}

bool ImageIO::save_image(std::string const& path, cv::Mat image) {
  cv::imwrite(path, image);
  return true;
}
