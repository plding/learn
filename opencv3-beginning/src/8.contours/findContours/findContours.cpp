#include <opencv2/opencv.hpp>
using namespace cv;

#include <iostream>
using namespace std;

int main()
{
    Mat srcImage = imread("findContours.jpg", 0);
    Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
    imshow("source", srcImage);

    srcImage = srcImage > 119;
    imshow("result", srcImage);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    for (int index = 0; index >= 0; index = hierarchy[index][0]) {
        Scalar color(rand() & 255, rand() & 255, rand() & 255);
        drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
    }

    imshow("contours image", dstImage);

    waitKey(0);
    return 0;
}
