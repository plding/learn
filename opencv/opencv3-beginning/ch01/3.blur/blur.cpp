#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main(void)
{
    Mat srcImage = imread("3.jpg");

    Mat dstImage;
    blur(srcImage, dstImage, Size(7, 7));
    imshow("blur rendering", dstImage);

    waitKey(0);
    return 0;
}
