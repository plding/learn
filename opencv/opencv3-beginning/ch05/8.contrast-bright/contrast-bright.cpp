#include <opencv2/opencv.hpp>
using namespace cv;

Mat g_srcImage, g_dstImage;
int g_contrast = 80;
int g_bright   = 80;

void changeContrastAndBright(int value, void *data);

int main()
{
    g_srcImage = imread("8.jpg");
    g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

    namedWindow("result");

    createTrackbar("Contrast", "result", &g_contrast, 300, changeContrastAndBright);
    createTrackbar("Bright", "result", &g_bright, 200, changeContrastAndBright);

    changeContrastAndBright(0, NULL);

    waitKey(0);
    return 0;
}

void changeContrastAndBright(int value, void *data)
{
    for (int i = 0; i < g_srcImage.rows; ++i) {
        for (int j = 0; j < g_srcImage.cols; ++j) {
            for (int c = 0; c < 3; ++c) {
                g_dstImage.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(
                        g_contrast * 0.01 * g_srcImage.at<Vec3b>(i, j)[c] + g_bright);
            }
        }
    }

    imshow("result", g_dstImage);
}
