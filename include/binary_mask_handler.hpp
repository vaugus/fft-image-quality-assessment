#ifndef BINARY_MASK_HANDLER_HPP
#define BINARY_MASK_HANDLER_HPP

#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <vector>
#include "../include/abstract_handler.hpp"
#include "opencv4/opencv2/core.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/highgui.hpp"

class BinaryMaskHandler : public AbstractHandler {
  public:
    std::map<int, double> cosines;
    std::map<int, double> sines;
    std::vector<int> angles;

    void init_angle_functions_with_steps(int step, int limit);
    double compute_vector_head(int y, int x, int angle);
    cv::Mat create_radial_vector_mask(int y, int x);

    std::string handle(std::string request) override;
};

#endif