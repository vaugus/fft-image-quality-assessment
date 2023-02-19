#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "opencv4/opencv2/core.hpp"

struct Request {
  cv::Mat image;
  double quality_index = 0;
};

class Handler {
  public:
    virtual Handler *set_next(Handler *handler) = 0;
    virtual Request handle(Request request) = 0;
};

#endif