#include <opencv2/opencv.hpp>
using namespace cv;

Mat g_srcImage;

void on_boxFilter(int value, void *data);
void on_meanBlur(int value, void *data);
void on_gaussianBlur(int value, void *data);

int main()
{
    g_srcImage = imread("4.jpg");
    imshow("source image", g_srcImage);

    // box filter
    int boxFilterValue = 3;
    namedWindow("box filter");
    createTrackbar("kernel", "box filter", &boxFilterValue, 40, on_boxFilter);
    on_boxFilter(boxFilterValue, NULL);

    // mean blur
    int meanBlurValue = 3;
    namedWindow("mean blur");
    createTrackbar("kernel", "mean blur", &meanBlurValue, 40, on_meanBlur);
    on_meanBlur(meanBlurValue, NULL);

    // gaussian blur
    int gaussianBlurValue = 3;
    namedWindow("gaussian blur");
    createTrackbar("kernel", "gaussian blur", &gaussianBlurValue, 40, on_gaussianBlur);
    on_gaussianBlur(gaussianBlurValue, NULL);

    waitKey(0);
    return 0;
}

void on_boxFilter(int value, void *data)
{
    Mat result;
    boxFilter(g_srcImage, result, -1, Size(value + 1, value + 1));
    imshow("box filter", result);
}

void on_meanBlur(int value, void *data)
{
    Mat result;
    blur(g_srcImage, result, Size(value + 1, value + 1), Point(-1, -1));
    imshow("mean blur", result);
}

void on_gaussianBlur(int value, void *data)
{
    Mat result;
    GaussianBlur(g_srcImage, result, Size(value * 2 + 1, value * 2 + 1), 0, 0);
    imshow("gaussian blur", result);
}
