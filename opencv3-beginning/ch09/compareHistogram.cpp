#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

#include <iostream>

int main()
{
    Mat image1 = imread("../images/book01.jpg");
    Mat image2 = imread("../images/book02.jpg");
    Mat image3 = imread("../images/book03.jpg");

    imshow("Image 1", image1);
    imshow("Image 2", image2);
    imshow("Image 3", image3);

    MatND hist1, hist2, hist3;
    int channels[] = {0, 1, 2};
    int histSize[] = {256, 256, 256};
    float hranges[] = {0.0, 255.0};
    const float *ranges[] = {hranges, hranges, hranges};

    calcHist(&image1, 1, channels, Mat(), hist1, 3, histSize, ranges);
    calcHist(&image2, 1, channels, Mat(), hist2, 3, histSize, ranges);
    calcHist(&image3, 1, channels, Mat(), hist3, 3, histSize, ranges);

    std::cout << "compare with image1 and image1: " << compareHist(hist1, hist1, HISTCMP_CORREL) << std::endl;
    std::cout << "compare with image1 and image2: " << compareHist(hist1, hist2, HISTCMP_CORREL) << std::endl;
    std::cout << "compare with image1 and image3: " << compareHist(hist1, hist3, HISTCMP_CORREL) << std::endl;
    std::cout << "compare with image2 and image3: " << compareHist(hist2, hist3, HISTCMP_CORREL) << std::endl;

    waitKey();
    return 0;
}
