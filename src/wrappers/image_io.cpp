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

cv::Mat ImageIO::grayscale(cv::Mat image) {
  cv::Mat grayscale;
  cv::cvtColor(image, grayscale, cv::COLOR_BGR2GRAY);
  return grayscale;
}

void ImageIO::save_as_yaml(std::string path, cv::Mat image) {
  cv::FileStorage file(path, cv::FileStorage::WRITE);
  file << "matrix" << image;
  file.release();
}

cv::Mat ImageIO::read_from_yaml(std::string path) {
  cv::FileStorage file(path, cv::FileStorage::READ);
  cv::Mat result;
  file["matrix"] >> result;
  file.release();

  return result;
}
  