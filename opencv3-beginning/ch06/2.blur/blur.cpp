#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    Mat image = imread("2.jpg");

    Mat result;
    blur(image, result, Size(7, 7));
    imshow("blur result", image);

    waitKey(0);
    return 0;
}
