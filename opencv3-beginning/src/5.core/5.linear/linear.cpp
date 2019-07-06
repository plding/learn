#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    Mat image1 = imread("mogu.jpg");
    Mat image2 = imread("rain.jpg");
    Mat dstImage;

    addWeighted(image1, 0.5, image2, 0.5, 0.0, dstImage);

    imshow("result", dstImage);
    waitKey(0);

    return 0;
}
