#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>

int main()
{
    cv::Mat image = cv::imread("../images/church01.jpg", 0);
    cv::imshow("Original Image", image);

    cv::Mat cornerStength;
    cv::cornerHarris(image, cornerStength, 3, 3, 0.01);

    double maxValue;
    minMaxLoc(cornerStength, NULL, &maxValue);

    cv::Mat corners;
    cv::threshold(cornerStength, corners, 0.01 * maxValue, 255, cv::THRESH_BINARY);
    corners.convertTo(corners, CV_8U);
    cv::imshow("Harris Corners", corners);

    cv::Mat dilated;
    cv::dilate(cornerStength, dilated, cv::Mat());
    corners &= (cornerStength == dilated);
    cv::imshow("Harris Corners with non-maxima suppression", corners);

    for (int y = 0; y < corners.rows; ++y) {
        const uchar *data = corners.ptr<uchar>(y);
        for (int x = 0; x < corners.cols; ++x) {
            if (data[x]) {
                circle(image, cv::Point(x, y), 3, cv::Scalar(255), 1);
            }
        }
    }
    cv::imshow("Circle Image", image);

    cv::waitKey();
    return 0;
}
