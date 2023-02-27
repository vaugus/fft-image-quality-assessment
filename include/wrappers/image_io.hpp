#ifndef IMAGE_IO_HPP
#define IMAGE_IO_HPP

#include "opencv4/opencv2/core.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/imgcodecs.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include "../wrappers/draw.hpp"

class ImageIO {
  private:
    Draw *draw;

  public:
    ImageIO(Draw *draw);

    cv::Mat open_image(std::string const& path);
    bool save_image(std::string const& path, cv::Mat image);
    cv::Mat grayscale(cv::Mat image);
    void save_as_yaml(std::string path, cv::Mat image);
    cv::Mat read_from_yaml(std::string path);
};

#endif