#include <opencv2/opencv.hpp>
using namespace cv;

Mat g_srcImage = imread("cat.jpg");

int g_type   = 0;
int g_kernel = 1;

void on_trackbarNumChange(int value, void *data);

int main()
{
    int type = 0;
    int kernel = 1;

    namedWindow("result");
    createTrackbar("type", "result", &g_type, 1, on_trackbarNumChange);
    createTrackbar("kernel", "result", &g_kernel, 10, on_trackbarNumChange);
    on_trackbarNumChange(0, NULL);

    waitKey(0);
    return 0;
}

void on_trackbarNumChange(int value, void *data)
{
    Mat result;
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_kernel + 1, 2 * g_kernel + 1),
            Point(g_kernel, g_kernel));

    if (g_type == 0) {
        erode(g_srcImage, result, element);
    } else {
        dilate(g_srcImage, result, element);
    }

    imshow("result", result);
}
