#include <opencv2/opencv.hpp>
using namespace cv;

#include <iostream>

int main()
{
    Mat image = imread("1.jpg");
    
    for (int i = 0; i < image.rows; ++i) {
        uchar *data = image.ptr<uchar>(i);
        for (int j = 0; j < image.cols * image.channels(); ++j) {
            data[j] = data[j] / 32 * 32; 
        }
    }

    imshow("result", image);
    waitKey(0);

    return 0;
}
