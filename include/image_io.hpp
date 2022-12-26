#ifndef IMAGE_IO_HPP
#define IMAGE_IO_HPP

#include "opencv4/opencv2/core.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/imgcodecs.hpp"
#include "opencv4/opencv2/highgui.hpp"

class ImageIO {

public:
    cv::Mat open_image(std::string const& path);
    bool save_image(std::string const& path, cv::Mat image);
};

#endif