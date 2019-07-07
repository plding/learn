#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

#include <iostream>

int main()
{
    Mat image = imread("../images/material01.jpg");
    imshow("Original Image", image);

    MatND hist;
    int size = 256;
    int channels[] = {0, 1, 2};
    int histSize[] = {size, size, size};
    float hranges[]= {0.0, 255.0};
    const float *ranges[] = {hranges, hranges, hranges};

    calcHist(&image, 1, channels, Mat(), hist, 3, histSize, ranges);

    //double maxValue;
    //minMaxLoc(hist, NULL, &maxValue);
    //std::cout << maxValue << std::endl;

    //Mat histImg(size, size, CV_8UC3, Scalar::all(255));

    //int hpt = static_cast<int>(size * 0.9);
    // for (int i = 0; i < size; ++i) {
    //     float blue  = hist.at<float>(i, 0, 0); 
    //     float green = hist.at<float>(0, i, 0); 
    //     float red   = hist.at<float>(0, 0, i); 
    //     int blueIntensity  = static_cast<int>(blue * hpt / 255); 
    //     int greenIntensity = static_cast<int>(green * hpt / 255); 
    //     int redIntensity   = static_cast<int>(red * hpt / 255); 

    //     line(histImg, Point(i, size), Point(i, 1 - blueIntensity), Scalar(255, 0, 0));
    // }

    // imshow("RGB Histogram", histImg);

    waitKey();
    return 0;
}
