#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/tracking.hpp>

#include <vector>
#include <iostream>

int main()
{
    cv::Mat image1 = cv::imread("../resources/church01.jpg", 0);
    cv::Mat image2 = cv::imread("../resources/church02.jpg", 0);

    cv::imshow("Original Image 1", image1);
    cv::imshow("Original Image 2", image2);

    // The first thing we need to do is get the features we want to track.
    std::vector<cv::Point2f> corners1, corners2;
    cv::goodFeaturesToTrack(image1,         // Image to track
                            corners1,       // Vector of detected corners (output)
                            500,            // Keep up to this many corners
                            0.01,           // Quality level (percent of maximum)
                            5,              // Min distance between corners
                            cv::noArray(),  // Mask
                            3,              // Block size
                            false,          // true: Harris, false: Shi-Tomasi
                            0.04);          // method specific parameter
    std::cout << "found by goodFeaturesToTrack: " << corners1.size() << std::endl;
    std::cout << "first corner: " << corners1[0].x << "," << corners1[0].y << std::endl;

    cv::cornerSubPix(image1,                // Input Image
                     corners1,              // Vector of corners (input and output)
                     cv::Size(10, 10),      // Half side length of search window
                     cv::Size(-1, -1),      // Half side length of dead zone (-1=none)
                     cv::TermCriteria(
                         cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,
                         20,                // Maximum number of iterations
                         0.03               // Maximum change per iteration
                        ));
    std::cout << "after cornerSubPix: " << corners1.size() << std::endl;
    std::cout << "first corner: " << corners1[0].x << "," << corners1[0].y << std::endl;

    // Call the Lucas Kanade algorithm
    std::vector<uchar> features_found;
    cv::calcOpticalFlowPyrLK(image1,
                             image2,
                             corners1,
                             corners2,
                             features_found,
                             cv::noArray(),
                             cv::Size(21, 21),
                             5,
                             cv::TermCriteria(
                                 cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,
                                 20,
                                 0.03));

    cv::waitKey();
    return 0;
}
