#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

#include "edgedetector.h"
#include "linefinder.h"

#define PI 3.1415926

int main()
{
    cv::Mat image = cv::imread("../images/road.jpg", 0);
    cv::imshow("Original Image", image);

    EdgeDetector ed;
    ed.computeSobel(image);
    cv::imshow("Sobel (orientation)", ed.getSobelOrientationImage());
    cv::imshow("Sobel (low threshold)", ed.getBinaryMap(125));
    cv::imshow("Sobel (high threshold)", ed.getBinaryMap(350));

    cv::Mat contours, contoursInv;
    cv::Canny(image, contours, 125, 350);
    cv::threshold(contours, contoursInv, 128, 255, cv::THRESH_BINARY_INV);
    cv::imshow("Canny contours", contoursInv);

    // cv::Mat test(200, 200, CV_8U, cv::Scalar(0));
    // cv::line(test, cv::Point(100, 0), cv::Point(200, 200), cv::Scalar(255));
    // cv::line(test, cv::Point(0, 50), cv::Point(200, 200), cv::Scalar(255));
    // cv::line(test, cv::Point(0, 200), cv::Point(200, 0), cv::Scalar(255));
    // cv::line(test, cv::Point(200, 0), cv::Point(0, 200), cv::Scalar(255));
    // cv::line(test, cv::Point(100, 0), cv::Point(100, 200), cv::Scalar(255));
    // cv::line(test, cv::Point(0, 100), cv::Point(200, 100), cv::Scalar(255));
    // cv::imshow("Test Image", test);

    std::vector<cv::Vec2f> lines;
    cv::HoughLines(contours, lines, 1, PI / 180, 60);

    cv::Mat result;
    image.copyTo(result);

    std::cout << "Lines detected: " << lines.size() << std::endl;

    auto it = lines.begin();
    while (it != lines.end()) {
        float rho   = (*it)[0]; // first element is distant rho
        float theta = (*it)[1]; // second element is angle theta

        cv::Point pt1, pt2;
        if (theta < PI / 4 || theta > 3 * PI / 4) {
            pt1 = cv::Point(rho / cos(theta), 0);
            pt2 = cv::Point((rho - result.rows * sin(theta)) / cos(theta), result.rows);
        } else {
            pt1 = cv::Point(0, rho / sin(theta));
            pt2 = cv::Point(result.cols, (rho - result.cols * cos(theta)) / sin(theta));
        }

        cv::line(result, pt1, pt2, cv::Scalar(255), 1);
        ++it;
    }

    cv::imshow("Detected Lines wit Hough", result);

    LineFinder ld;

    ld.setLineLengthAndGap(100, 20);
    ld.setMinVote(80);

    std::vector<cv::Vec4i> li = ld.findLines(contours);
    ld.drawDetectedLines(image);
    cv::imshow("Detected Lines with HoughP", image);

    auto it2 = li.begin();
    while (it2 != li.end()) {
        std::cout << "(" << (*it2)[0] << "," << (*it2)[1] << ")-(" << (*it2)[2] << "," << (*it2)[3]
                  << ")" << std::endl;
        ++it2;
    }

    cv::waitKey();
    return 0;
}
