#ifndef MASK_LOOKUP_HPP
#define MASK_LOOKUP_HPP

#include <map>
#include <mutex>
#include "opencv4/opencv2/core.hpp"

class MaskLookup {
  private:
    static MaskLookup *instance;
    static std::mutex mutex;
    
    MaskLookup();
    ~MaskLookup();
  public:

    std::map<std::pair<int, int>, cv::Mat> index;

    MaskLookup(MaskLookup &other) = delete;
    void operator=(const MaskLookup &) = delete;
    static MaskLookup *get_instance();

    bool mask_exists(int width, int height);
    cv::Mat of(int width, int height);
    void insert(cv::Mat mask);
    int size();
};

#endif
