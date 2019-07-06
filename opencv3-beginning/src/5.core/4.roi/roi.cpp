#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    Mat image = imread("dota_pa.jpg");
    Mat logo  = imread("dota_logo.jpg");

    Mat roi  = image(Rect(200, 250, logo.cols, logo.rows));
    Mat mask = imread("doto_logo.jpg", 0);
    logo.copyTo(roi, mask);

    imshow("result", image);
    waitKey(0);

    return 0;
}
