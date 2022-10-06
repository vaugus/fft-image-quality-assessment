#ifndef SAMPLE_CPP
#define SAMPLE_CPP

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class TestUtils {

public:

    void draw_elipse(cv::Mat image, cv::Point center, double angle);
    void draw_filled_circle(cv::Mat image, cv::Point center);
    cv::Mat create_atom_image();
};

#endif