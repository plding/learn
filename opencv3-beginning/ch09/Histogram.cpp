#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

int main()
{
    Mat image = imread("../images/material01.jpg", 0);
    imshow("Original Image", image);

    MatND hist;
    int channels = 0;
    int histSize = 256;
    float hranges[] = {0.0, 255.0};
    const float *ranges[] = {hranges};

    calcHist(&image, 1, &channels, Mat(), hist, 1, &histSize, ranges);

    double maxValue;
    minMaxLoc(hist, NULL, &maxValue);

    Mat histImg(histSize, histSize, CV_8U, Scalar(255));

    int hpt = static_cast<int>(histSize * 0.9);
    for (int i = 0; i < histSize; ++i) {
        float binValue = hist.at<float>(i);
        int intensity  = static_cast<int>(binValue * hpt / maxValue);

        line(histImg, Point(i, histSize), Point(i, histSize - intensity), Scalar(0));
    }

    imshow("Histogram", histImg);

    waitKey();
    return 0;
}
