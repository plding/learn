#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>

#include <iostream>
#include <vector>

int main()
{
    cv::Mat image = cv::imread("../images/church01.jpg", 0);
    cv::imshow("Original Image", image);

    std::vector<cv::Point2f> points;
    goodFeaturesToTrack(image, points, 500, 0.01, 10);
    std::cout << "Found " << points.size() << " feature points" << std::endl;

    for (auto it = points.begin(); it != points.end(); ++it)
        circle(image, *it, 3, cv::Scalar(255), 1);
    cv::imshow("Circle Image", image);

    cv::waitKey();
    return 0;
}
