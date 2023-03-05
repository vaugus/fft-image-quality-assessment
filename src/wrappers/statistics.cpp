#include "../../include/wrappers/statistics.hpp"

double Statistics::kurtosis(std::vector<double> data) {
  return (moment(data, 4) / std::pow(moment(data, 2), 2)) - 3.0;
}

double Statistics::moment(std::vector<double> data, const int r) {
  double avg = mean(data);

  double mr = 0.0;
  std::vector<double>::iterator it;
  
  for (it = data.begin(); it != data.end(); ++it) {
      mr += std::pow(*it - avg, r);
  }

  return mr / data.size();
}

double Statistics::mean(std::vector<double> data) {
  return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}