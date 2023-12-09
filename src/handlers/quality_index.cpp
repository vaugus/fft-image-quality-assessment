#include "../../include/handlers/quality_index.hpp"
#include "../../include/wrappers/statistics.hpp"

extern Statistics *statistics;

double QualityIndex::compute_index(cv::Mat image) {
  SpectrumAnalysis analysis = SpectrumAnalysis::builder()
    .prepare_image(image)
    .apply_fft()
    .apply_mask()
    .compute_maximum_absolute_value()
    .filter_absolute_values_with_threshold(1000.0)
    .build();

  std::vector<double> index_data = analysis.get_kurtosis_eligible_values();

  std::transform(index_data.begin(), index_data.end(), index_data.begin(),
    [](double value) -> double { 
      return pow(value, 3);
    });

  return statistics->kurtosis(index_data);
}

Request QualityIndex::handle(Request request) {
  return AbstractHandler::handle(request);
}