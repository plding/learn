#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
using namespace cv;

#include <iostream>

int main()
{
    Mat image = imread("../images/church.jpg", 0);
    imshow("Original Image", image);

    Mat cornerStrength;
    cornerHarris(image, cornerStrength, 3, 3, 0.1);

    double maxValue;
    minMaxLoc(cornerStrength, NULL, &maxValue); 

    Mat corners;
    threshold(cornerStrength, corners, 0.01 * maxValue, 255, THRESH_BINARY);
    corners.convertTo(corners, CV_8U);
    imshow("Harris Corners", corners);

    Mat dilated;
    dilate(image, dilated, Mat());
    corners &= (image == dilated);
    imshow("Harris Corners with non-maxima suppression", corners);

    for (int i = 0; i < corners.rows; ++i) {
        const uchar *data = corners.ptr<uchar>(i);
        for (int j = 0; j < corners.cols; ++j) {
            if (data[j]) {
                circle(image, Point(j, i), 3, Scalar(255), 1);
            }
        }
    }

    imshow("Image with corners", image);

    waitKey();
    return 0;
}
