#include "../include/test_utils.hpp"

void TestUtils::draw_elipse(cv::Mat image, cv::Point center, double angle)
{
    int thickness = 2;
    int line_type = 8;
    int width = image.rows;

    ellipse(image,
            center,
            cv::Size(width / 4, width / 16),
            angle,
            0,
            360,
            cv::Scalar(255, 0, 0),
            thickness,
            line_type);
}

void TestUtils::draw_filled_circle(cv::Mat image, cv::Point center)
{
    int width = image.rows;

    circle(image,
           center,
           width / 32,
           cv::Scalar(0, 0, 255),
           cv::FILLED,
           cv::LINE_8);
}

cv::Mat TestUtils::create_atom_image()
{
    int width = 400;
    cv::Mat atom = cv::Mat::zeros(width, width, CV_8UC3);
    cv::Point center = cv::Point(width / 2, width / 2);

    auto elipse = [this, atom, center](double angle)
    {
        draw_elipse(atom, center, angle);
    };

    elipse(90);
    elipse(0);
    elipse(45);
    elipse(-45);

    draw_filled_circle(atom, center);

    return atom;
}