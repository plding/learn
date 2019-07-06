#include <opencv2/opencv.hpp>
using namespace cv;

int main(void)
{
    VideoCapture capture("5.avi");

    while (1) {
        Mat frame;
        capture >> frame;
        imshow("video", frame);
        waitKey(30);
    } 

    return 0;
}
