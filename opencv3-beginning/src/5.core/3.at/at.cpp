#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    Mat image = imread("1.jpg");

    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            Vec3b &point = image.at<Vec3b>(i, j);
            point[0] = point[0] / 32 * 32;
            point[1] = point[1] / 32 * 32;
            point[2] = point[2] / 32 * 32;
        }
    }

    imshow("result", image);
    waitKey(0);

    return 0;
}
