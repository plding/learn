#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main(void)
{
    Mat srcImage = imread("2.jpg");
    
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    Mat dstImage;
    erode(srcImage, dstImage, element);
    imshow("ercode rendering", dstImage);

    waitKey(0);
    return 0;
}
