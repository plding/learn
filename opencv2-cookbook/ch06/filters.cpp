#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
    cv::Mat gauss = cv::getGaussianKernel(9, 1.5, CV_32F);
    std::cout << "[";
    for (auto it = gauss.begin<float>(), itend = gauss.end<float>(); it != itend; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "]" << std::endl;

    gauss = cv::getGaussianKernel(9, 0.5, CV_32F);
    std::cout << "[";
    for (auto it = gauss.begin<float>(), itend = gauss.end<float>(); it != itend; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "]" << std::endl;

    gauss = cv::getGaussianKernel(9, 2.5, CV_32F);
    std::cout << "[";
    for (auto it = gauss.begin<float>(), itend = gauss.end<float>(); it != itend; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "]" << std::endl;

    cv::Mat image = cv::imread("../images/boldt.jpg", 0);
    cv::imshow("Original Image", image);

    // Blur the image with gaussian filter
    cv::Mat result;
    cv::GaussianBlur(image, result, cv::Size(5, 5), 1.5);
    cv::imshow("Gaussian filtered Image", result);

    // Blur the image with a mean filter
    cv::blur(image, result, cv::Size(5, 5));
    cv::imshow("Mean filtered Image", result);

    image = cv::imread("../images/salted.bmp", 0);
    cv::imshow("S&P Image", image);

    // Blur the image with a mean filter
    cv::blur(image, result, cv::Size(5, 5));
    cv::imshow("Mean filtered S&P Image", result);

    // Blur the image with a median filter
    cv::medianBlur(image, result, 5);
    cv::imshow("Median filtered S&P Image", result);

    cv::waitKey();
    return 0;
}
