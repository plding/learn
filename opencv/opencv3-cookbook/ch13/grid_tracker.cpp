#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/tracking.hpp>

int main()
{
    cv::Mat image1 = cv::imread(cv::samples::findFile("goose/goose130.bmp"), 0);
    cv::Mat image2 = cv::imread(cv::samples::findFile("goose/goose131.bmp"), 0);

    // define a regular grid of points
    std::vector<cv::Point2f> grid;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cv::Point2f p(290 + i * 6.5, 100 + j * 4.0);
            grid.push_back(p);
        }
    }

    // track in next image
    std::vector<cv::Point2f> newPoints;
    std::vector<uchar> status;
    std::vector<float> err;

    // track the points
    cv::calcOpticalFlowPyrLK(image1, image2, // 2 consecutive images
        grid,       // input point position in first image
        newPoints,  // output point position in the second image
        status,     // tracking success
        err);       // tracking error

    // draw the points
    for (cv::Point2f p : grid) {
        cv::circle(image1, p, 1, cv::Scalar::all(255), -1);
    }
    cv::imshow("Initial points", image1);

    for (cv::Point2f p : newPoints) {
        cv::circle(image2, p, 1, cv::Scalar::all(255), -1);
    }
    cv::imshow("Tracked points", image2);

    cv::waitKey();
    return 0;
}
