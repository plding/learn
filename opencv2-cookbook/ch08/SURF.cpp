#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>

#include <vector>

int main()
{
    cv::Mat image = cv::imread("../images/church01.jpg", 0);
    if (!image.data)
        return -1;

    cv::imshow("Original Image", image);

    std::vector<cv::KeyPoint> keypoints;
    auto surf = cv::xfeatures2d::SURF::create(2500);
    surf->detect(image, keypoints);

    cv::drawKeypoints(image, keypoints, image, cv::Scalar::all(255),
                      cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imshow("SURF Features", image);

    cv::waitKey();
    return 0;
}
