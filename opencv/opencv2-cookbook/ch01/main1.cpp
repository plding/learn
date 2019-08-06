#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

int main()
{
    cv::Mat image = cv::imread("../images/image.jpg");

    cv::namedWindow("My Image");

    cv::imshow("My Image", image);

    cv::waitKey(5000);

    return 0;
}
