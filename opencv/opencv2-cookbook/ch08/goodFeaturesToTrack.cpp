#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <vector>

int main()
{
    cv::Mat image = cv::imread("../images/church01.jpg", 0);
    cv::imshow("Original Image", image);

    std::vector<cv::Point2f> corners;
    cv::goodFeaturesToTrack(image, corners,
                            500,    // maximum number of corners to be returned
                            0.01,   // quality level
                            10);    // minimum allowed distance between points

    std::cout << "Find " << corners.size() << " feature points" << std::endl;
    for (auto it = corners.begin(); it != corners.end(); ++it)
        cv::circle(image, *it, 3, cv::Scalar(255, 255, 255), 1);
    
    cv::imshow("Good Features to Track", image);

    cv::waitKey();
    return 0;
}
