#include "../../include/model/mask_lookup.hpp"

MaskLookup *MaskLookup::instance { nullptr };
std::mutex MaskLookup::mutex;

MaskLookup::MaskLookup() {}

MaskLookup::~MaskLookup() {}

MaskLookup *MaskLookup::get_instance() {
  std::lock_guard<std::mutex> lock(MaskLookup::mutex);
  if (MaskLookup::instance == nullptr)
    instance = new MaskLookup();

  return instance;
}

bool MaskLookup::mask_exists(int width, int height) {
  if (this->index.empty()) return {};
  return this->index.count({ width, height });
}

cv::Mat MaskLookup::of(int width, int height) {
  if (this->index.empty())
    return {};

  std::map<std::pair<int,int>, cv::Mat>::iterator it;
  it = this->index.find({ width, height });

  if (it != this->index.end()) 
    return it->second;

  return {};
}

void MaskLookup::insert(cv::Mat mask) {
  this->index[{mask.cols, mask.rows}] = mask;
}
