#include "../include/image_io.hpp"

cv::Mat ImageIO::open_image(std::string const& path) {
  return cv::imread(path);
}

bool ImageIO::save_image(std::string const& path, cv::Mat image) {
  cv::imwrite(path, image);
  return true;
}
