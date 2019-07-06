#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    Mat srcImage = imread("resize.jpg");
    Mat dstImage1, dstImage2;

    resize(srcImage, dstImage1, Size(srcImage.cols / 2, srcImage.rows / 2));
    resize(srcImage, dstImage2, Size(srcImage.cols * 2, srcImage.rows * 2));

    imshow("source image", srcImage);
    imshow("smaller image", dstImage1);
    imshow("larger image", dstImage2);
    
    waitKey(0);
    return 0;
}
