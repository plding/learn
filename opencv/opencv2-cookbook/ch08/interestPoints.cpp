#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

#include "harriscorners.h"

int main()
{
    cv::Mat image = cv::imread("../images/church01.jpg", 0);
    cv::imshow("Original Image", image);

    cv::Mat cornerStrength;
    cv::cornerHarris(image, cornerStrength,
                     3,     // neighborhood size
                     3,     // aperture size
                     0.01); // Harris parameter

    cv::Mat harrisCorners;
    double threshold = 0.0001;
    cv::threshold(cornerStrength, harrisCorners, threshold, 255, cv::THRESH_BINARY_INV);
    cv::imshow("Harris Corner Map", harrisCorners);

    HarrisDetector harris;
    harris.detect(image);
    std::vector<cv::Point> pts;
    harris.getCorners(pts, 0.01);
    harris.drawOnImage(image, pts);
    cv::imshow("Harris Corners", image);

    cv::waitKey();
    return 0;
}
