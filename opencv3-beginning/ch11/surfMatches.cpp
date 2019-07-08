#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
using namespace cv;

#include <vector>

int main()
{
    Mat image1 = imread("../images/book02.jpg", 0);
    Mat image2 = imread("../images/book03.jpg", 0);

    imshow("Image 1", image1);
    imshow("Image 2", image2);

    auto surf = cv::xfeatures2d::SURF::create(2500);
    std::vector<KeyPoint> keypoints1, keypoints2;
    surf->detect(image1, keypoints1);
    surf->detect(image2, keypoints2);

    Mat descriptors1, descriptors2;
    surf->compute(image1, keypoints1, descriptors1);
    surf->compute(image2, keypoints2, descriptors2);

    auto matcher = BFMatcher::create();
    std::vector<DMatch> matches;
    matcher->match(descriptors1, descriptors2, matches);

    Mat imageMatches;
    drawMatches(image1, keypoints1,
                image2, keypoints2,
                matches,
                imageMatches,
                Scalar::all(255));
    imshow("Matches", imageMatches);

    waitKey();
    return 0;
}
