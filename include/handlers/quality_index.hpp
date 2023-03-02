#ifndef QUALITY_INDEX_HANDLER_HPP
#define QUALITY_INDEX_HANDLER_HPP

#include <algorithm>
#include "abstract_handler.hpp"
#include "../model/spectrum_analysis.hpp"

class QualityIndex : public AbstractHandler {
  public:
    double compute_index(cv::Mat image);
    Request handle(Request request) override;
};

#endif