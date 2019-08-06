#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat src, src_gray, dst;
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    const char *window_name = "Laplace Demo";

    const char *imageName = argc >= 2 ? argv[1] : "../data/lena.jpg";
    src = imread(imageName, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Error opening image" << endl;
        cout << "Program Arguments: [image_name -- default ../data/lena.jpg]" << endl;
        return -1;
    }

    GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    Mat abs_dst;
    Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(dst, abs_dst);

    imshow(window_name, abs_dst);
    waitKey(0);

    return 0;
}
