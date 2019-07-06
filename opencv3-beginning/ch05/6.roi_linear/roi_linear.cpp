#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    Mat image = imread("dota_pa.jpg");
    Mat logo  = imread("dota_logo.jpg");

    Mat roi = image(Range(250, 250 + logo.rows), Range(200, 200 + logo.cols));
    addWeighted(roi, 0.5, logo, 0.3, 0.0, roi);

    imshow("result", image);
    waitKey(0);

    return 0;
}
