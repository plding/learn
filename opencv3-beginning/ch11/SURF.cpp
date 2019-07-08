#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>

#include <vector>

int main()
{
    cv::Mat image1 = cv::imread("../images/book02.jpg", 0);
    cv::Mat image2 = cv::imread("../images/book03.jpg", 0);

    cv::imshow("Image 1", image1);
    cv::imshow("Image 2", image2);

    auto surf = cv::xfeatures2d::SURF::create(2500);
    std::vector<cv::KeyPoint> keypoints1, keypoints2;

    surf->detect(image1, keypoints1);
    surf->detect(image2, keypoints2);

    cv::drawKeypoints(image1, keypoints1, image1, cv::Scalar::all(255), cv::DrawMatchesFlags::DEFAULT);
    cv::drawKeypoints(image2, keypoints2, image2, cv::Scalar::all(255), cv::DrawMatchesFlags::DEFAULT);

    cv::imshow("Circle Image 1", image1);
    cv::imshow("Circle Image 2", image2);

    cv::waitKey();
    return 0;
}
