#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main(void)
{
    Mat srcImage = imread("4.jpg");
    Mat edge, grayImage;

    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
    blur(grayImage, edge, Size(3, 3)); 
    Canny(edge, edge, 3, 9, 3);

    imshow("canny result", edge);
    waitKey(0);
    return 0;
}
