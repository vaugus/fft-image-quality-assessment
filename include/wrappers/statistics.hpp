#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <vector>

class Statistics {
  public:
    double kurtosis(std::vector<double> data);
    double moment(std::vector<double> data, int r);
    double mean(std::vector<double> data);
};

#endif