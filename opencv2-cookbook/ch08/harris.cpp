#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
    cv::Mat image = cv::imread("../images/image.jpg", 0);
    cv::imshow("Original Image", image);

    cv::Mat roi = image(cv::Rect(180, 90, 140, 140));

    cv::Mat cornerStrength;
    cv::cornerHarris(roi, cornerStrength, 3, 3, 0.1);

    double maxStrength;
    cv::minMaxLoc(cornerStrength, NULL, &maxStrength);

    cv::Mat corners;
    cv::threshold(cornerStrength, corners, 0.01 * maxStrength, 255, cv::THRESH_BINARY);
    corners.convertTo(corners, CV_8U);
    cv::imshow("Harris Corners", corners);

    cv::Mat dilated;
    cv::dilate(cornerStrength, dilated, cv::Mat());
    corners &= (cornerStrength == dilated);
    cv::imshow("Harris Corners with non-maxima suppression", corners);

    for (int y = 0; y < corners.rows; ++y) {
        const uchar *row = corners.ptr<uchar>(y);
        for (int x = 0; x < corners.cols; ++x) {
            if (row[x]) {
                cv::circle(image, cv::Point(x + 180, y + 90), 3, cv::Scalar(255, 255, 255), 2);
            }
        }
    }
    cv::imshow("Circle Image", image);

    cv::waitKey();
    return 0;
}
