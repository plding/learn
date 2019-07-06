#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

int main()
{
    Mat image = imread("../images/material01.jpg");    
    cvtColor(image, image, COLOR_BGR2HSV);
    imshow("Original Image", image);

    waitKey();
    return 0;
}
