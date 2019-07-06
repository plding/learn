#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    Mat image = imread("1.jpg");
    Mat result;

    boxFilter(image, result, -1, Size(5, 5));

    imshow("box filter result", result);
    waitKey(0);

    return 0;
}
