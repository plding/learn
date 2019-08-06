#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

int main()
{
    cv::Mat image1 = cv::imread("../images/church01.jpg", 0);
    cv::Mat image2 = cv::imread("../images/church02.jpg", 0);
    if (!image1.data || !image2.data)
        return -1;

    cv::imshow("Image1", image1);
    cv::imshow("Image2", image2);

    std::vector<cv::KeyPoint> keypoints1;
    std::vector<cv::KeyPoint> keypoints2;

    auto surf = cv::xfeatures2d::SURF::create(2500);

    surf->detect(image1, keypoints1);
    surf->detect(image2, keypoints2);

    std::cout << "Number of SURF points (1): " << keypoints1.size() << std::endl;
    std::cout << "Number of SURF points (2): " << keypoints2.size() << std::endl;

    cv::Mat imageKP;
    cv::drawKeypoints(image1, keypoints1, imageKP, cv::Scalar::all(255),
                      cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imshow("Image1 SURF Features", imageKP);
    cv::drawKeypoints(image2, keypoints1, imageKP, cv::Scalar::all(255),
                      cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imshow("Image2 SURF Features", imageKP);

    cv::Mat descriptors1, descriptors2;
    surf->compute(image1, keypoints1, descriptors1);
    surf->compute(image2, keypoints2, descriptors2);
    std::cout << "descriptor1 matrix size: " << descriptors1.rows << " by "
              << descriptors1.cols << std::endl;
    std::cout << "descriptor2 matrix size: " << descriptors2.rows << " by "
              << descriptors2.cols << std::endl;

    auto matcher = cv::BFMatcher::create();
    std::vector<cv::DMatch> matches;
    matcher->match(descriptors1, descriptors2, matches);
    std::cout << "Number of matched points: " << matches.size() << std::endl;
    std::nth_element(matches.begin(),
                     matches.begin() + 24,
                     matches.end());
    matches.erase(matches.begin() + 25, matches.end());

    cv::Mat imageMatches;
    cv::drawMatches(image1, keypoints1,
                    image2, keypoints2,
                    matches,
                    imageMatches,
                    cv::Scalar::all(255));
    cv::imshow("Matches", imageMatches);

    cv::waitKey();
    return 0;
}
