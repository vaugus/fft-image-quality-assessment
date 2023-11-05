#ifndef UTIL_HPP
#define UTIL_HPP

#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

namespace util {
  inline double round(double value, int precision=6) {
    std::stringstream value_string;
    value_string << std::setprecision(precision) << std::fixed << value;
    return std::stod(value_string.str());
  }

  inline std::vector<double> read_doubles_from_file(std::string path) {
    std::vector<double> doubles;
    std::ifstream stream(path.c_str());
    if (!stream) return {};

    std::string line;
    while (std::getline(stream, line)) {
      if(line.size() > 0) {
        doubles.push_back(std::stold(line));
      }
    }

    stream.close();
    return doubles;
  }
};

#endif
