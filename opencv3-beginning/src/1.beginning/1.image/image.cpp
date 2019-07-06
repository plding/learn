#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    Mat srcImage = imread("1.jpg");
    imshow("Image", srcImage);
    waitKey(0);
    return 0;
}
