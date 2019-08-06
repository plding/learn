#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>

#include <vector>
#include <iostream>

int main()
{
    cv::Mat image = cv::imread("../images/church01.jpg", 0);
    cv::imshow("Original Image", image);

    std::vector<cv::KeyPoint> keypoints;
    auto gftt = cv::GFTTDetector::create(500, 0.01, 10);
    gftt->detect(image, keypoints);

    std::cout << "Found " << keypoints.size() << " feature points" << std::endl;

    cv::KeyPoint point = keypoints[0];
    std::cout << "angle: " << point.angle << std::endl;
    std::cout << "class_id " << point.class_id << std::endl;
    std::cout << "octave: " << point.octave << std::endl;
    std::cout << "pt: " << point.pt << std::endl;
    std::cout << "response: " << point.response << std::endl;
    std::cout << "size: " << point.size << std::endl;

    drawKeypoints(image, keypoints, image, cv::Scalar::all(255),
                  cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);
    cv::imshow("GFTT Features", image);

    cv::waitKey();
    return 0;
}
