#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

cv::Mat function()
{
    cv::Mat ima(240, 320, CV_8U, cv::Scalar(100));
    return ima;
}

int main()
{
    cv::Mat image;
    std::cout << "size: " << image.size().height << ", " << image.size().width << std::endl;

    image = cv::imread("../images/image.jpg");
    if (!image.data) {
        return 1;
    }

    std::cout << "size (after reading): " << image.size().height << ", " << image.size().width
              << std::endl;

    cv::namedWindow("Original Image");
    cv::imshow("Original Image", image);

    cv::Mat result;
    cv::flip(image, result, 1);

    cv::namedWindow("Output Image");
    cv::imshow("Output Image", result);

    cv::waitKey(0);
    cv::imwrite("output.bmp", result);

    cv::Mat image2, image3;

    image2 = result;
    result.copyTo(image3);

    cv::flip(result, result, 0);

    cv::namedWindow("image 2");
    cv::imshow("image 2", image2);
    cv::namedWindow("image 3");
    cv::imshow("image 3", image3);

    cv::Mat gray = function();
    cv::namedWindow("Gray Image");
    cv::imshow("Gray Image", gray);

    cv::waitKey(0);
    return 0;
}
