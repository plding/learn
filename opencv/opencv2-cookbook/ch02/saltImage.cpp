#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

void salt(cv::Mat &image, int n)
{
    for (int k = 0; k < n; ++k) {
        int i = rand() % image.rows;
        int j = rand() % image.cols;

        if (image.channels() == 1) {
            // gray-level image
            image.at<uchar>(i, j) = 255;

        } else if (image.channels() == 3) {
            // color image
            image.at<cv::Vec3b>(i, j)[0] = 255;
            image.at<cv::Vec3b>(i, j)[1] = 255;
            image.at<cv::Vec3b>(i, j)[2] = 255;
        }
    }
}

int main()
{
    srand(cv::getTickCount());

    cv::Mat image = cv::imread("../images/boldt.jpg", 0);

    salt(image, 3000);

    cv::namedWindow("Image");
    cv::imshow("Image", image);

    cv::imwrite("salted.bmp", image);

    cv::waitKey(5000);

    return 0;
}
