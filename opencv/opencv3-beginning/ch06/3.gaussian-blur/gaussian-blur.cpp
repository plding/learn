#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    Mat image = imread("3.jpg");
    imshow("source image", image);

    Mat result;
    GaussianBlur(image, result, Size(5, 5), 0, 0);
    imshow("gaussian blur result", result);

    waitKey(0);
    return 0;
}
