#include <opencv2/opencv.hpp>
using namespace cv;

Mat g_srcImage = imread("fruit.jpg");
int g_type = 0;
int g_kernel = 1;

void on_change(int value, void *data);

int main()
{
    namedWindow("result");
    createTrackbar("type", "result", &g_type, 1, on_change);
    createTrackbar("kernel", "result", &g_kernel, 10, on_change);
    on_change(0, NULL);

    waitKey(0);
    return 0;
}

void on_change(int value, void *data)
{
    Mat result;
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_kernel + 1, 2 * g_kernel + 1));

    if (g_type == 0) {
        morphologyEx(g_srcImage, result, MORPH_OPEN, element);
    } else {
        morphologyEx(g_srcImage, result, MORPH_CLOSE, element);
    }

    imshow("result", result);
}
