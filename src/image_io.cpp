#include "../include/image_io.hpp"

cv::Mat ImageIO::open_image(std::string const& path) {
    return cv::imread(path);
}