#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>

#include <vector>

int main()
{
    cv::Mat image = cv::imread("../images/church01.jpg", 0);
    cv::imshow("Original Image", image);

    std::vector<cv::KeyPoint> keypoints;
    auto fast = cv::FastFeatureDetector::create(40);
    fast->detect(image, keypoints);

    cv::drawKeypoints(image,                                   // original image
                      keypoints,                               // vector of keypoints
                      image,                                   // the resulting image
                      cv::Scalar(255, 255, 255),               // color of the points
                      cv::DrawMatchesFlags::DRAW_OVER_OUTIMG); // drawing flag

    cv::imshow("FAST Features", image);

    cv::waitKey();
    return 0;
}
