#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main()
{
    Mat image = imread("dota.jpg");
    Mat logo  = imread("dota_logo.jpg");

    Mat roi = image(Rect(800, 350, logo.cols, logo.rows));
    addWeighted(roi, 0.5, logo, 0.3, 0, roi);
    imshow("mixed result", image);

    waitKey(0);
    return 0;
}
