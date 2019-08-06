#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    Mat image = imread("1.jpg");

    Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
    Mat_<Vec3b>::iterator itend = image.end<Vec3b>();

    for ( ; it != itend; ++it) {
        (*it)[0] = (*it)[0] / 32 * 32;
        (*it)[1] = (*it)[1] / 32 * 32;
        (*it)[2] = (*it)[2] / 32 * 32;
    }

    imshow("result", image);
    waitKey(0);

    return 0;
}
