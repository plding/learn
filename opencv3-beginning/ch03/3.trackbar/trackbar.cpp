#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

const int MAX_ALPHA_VALUE = 100;

Mat g_srcImage1;
Mat g_srcImage2;

void on_Trackbar(int value, void *data);

int main()
{
    g_srcImage1 = imread("3.1.jpg");
    g_srcImage2 = imread("3.2.jpg");

    int value = 70;

    namedWindow("trackbar");
    createTrackbar("Alpha", "trackbar", &value, MAX_ALPHA_VALUE, on_Trackbar);
    on_Trackbar(value, NULL);

    waitKey(0);
    return 0;
}

void on_Trackbar(int value, void *data)
{
    double alphaValue1 = (double) value / MAX_ALPHA_VALUE;
    double alphaValue2 = 1 - alphaValue1;
    Mat dstImage;

    addWeighted(g_srcImage1, alphaValue1, g_srcImage2, alphaValue2, 0, dstImage);
    imshow("trackbar", dstImage);
}
