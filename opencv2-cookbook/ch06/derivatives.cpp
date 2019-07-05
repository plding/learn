#include <iomanip>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
    cv::Mat image = cv::imread("../images/boldt.jpg", 0);
    cv::imshow("Original Image", image);

    cv::Mat sobelX;
    cv::Sobel(image, sobelX, CV_8U, 1, 0, 3, 0.4, 128);
    cv::imshow("Sobel X Image", sobelX);

    cv::Mat sobelY;
    cv::Sobel(image, sobelY, CV_8U, 0, 1, 3, 0.4, 128);
    cv::imshow("Sobel Y Image", sobelY);

    cv::Sobel(image, sobelX, CV_16S, 1, 0);
    cv::Sobel(image, sobelY, CV_16S, 0, 1);
    cv::Mat sobel = abs(sobelX) + abs(sobelY);
    
    double sobmin, sobmax;
    cv::minMaxLoc(sobel, &sobmin, &sobmax);
    std::cout << "sobel value range: " << sobmin << " " << sobmax << std::endl;

    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            std::cout << std::setw(5) << static_cast<int>(sobel.at<short>(i + 135, j + 362)) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    cv::Mat sobelImage;
    sobel.convertTo(sobelImage, CV_8U, -255.0 / sobmax, 255);
    cv::imshow("Sobel Image", sobelImage);

    cv::Mat sobelThresholded;
    cv::threshold(sobelImage, sobelThresholded, 225, 255, cv::THRESH_BINARY);
    cv::imshow("Binary Sobel Image (low)", sobelThresholded);
    cv::threshold(sobelImage, sobelThresholded, 190, 255, cv::THRESH_BINARY);
    cv::imshow("Binary Sobel Image (high)", sobelThresholded);

    cv::waitKey();
    return 0;
}
