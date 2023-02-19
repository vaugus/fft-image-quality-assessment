#ifndef BINARY_MASK_HANDLER_HPP
#define BINARY_MASK_HANDLER_HPP

#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include "abstract_handler.hpp"
#include "../wrappers/draw.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/highgui.hpp"

class BinaryMaskHandler : public AbstractHandler {
  private:
    Draw *draw;

  public:
    std::map<int, double> cosines;
    std::map<int, double> sines;
    std::vector<int> angles;

    BinaryMaskHandler(Draw *draw);

    void init_angle_functions_with_steps(int step, int limit);
    double compute_vector_head(int y, int x, int angle);
    cv::Mat create_radial_vector_mask(int y, int x);

    Request handle(Request request) override;
};

#endif