#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

#include <iostream>

int main()
{
    Mat image = imread("../images/material01.jpg");    
    cvtColor(image, image, COLOR_BGR2HSV);
    imshow("Original Image", image);

    MatND hist;
    int hueSize = 30;
    int saturationSize = 32;
    float hueRanges[] = {0.0, 180.0};
    float saturationRanges[] = {0.0, 256.0};
    int channels[] = {0, 1};
    int histSize[] = {hueSize, saturationSize};
    const float *ranges[] = {hueRanges, saturationRanges};

    calcHist(&image,
             1,
             channels,
             Mat(),
             hist,
             2,
             histSize,
             ranges);

    double maxValue;
    minMaxLoc(hist, NULL, &maxValue);
    std::cout << maxValue << std::endl;

    int scale = 10;
    Mat histImg(saturationSize * scale, hueSize * scale, CV_8U, Scalar::all(255));

    for (int hue = 0; hue < hueSize; ++hue) {
        for (int saturation = 0; saturation < saturationSize; ++saturation) {
            float binValue = hist.at<float>(hue, saturation);
            int intensity  = static_cast<int>(binValue * 255 / maxValue);

            rectangle(histImg, Point(hue * scale, saturation * scale),
                      Point((hue + 1) * scale - 1, (saturation + 1) * scale - 1),
                      Scalar(intensity), FILLED);
        }
    }

    imshow("H-S Histogram", histImg);

    waitKey();
    return 0;
}
