#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    Mat srcImage = imread("canny.jpg");
    Mat dstImage, grayImage, edge;

    cvtColor(srcImage, grayImage, CV_BGR2GRAY);
    blur(grayImage, edge, Size(3, 3));
    Canny(edge, edge, 3, 9, 3);
    srcImage.copyTo(dstImage, edge);

    imshow("canny result", dstImage);
    waitKey(0);

    return 0;
}
