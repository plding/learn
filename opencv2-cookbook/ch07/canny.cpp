#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
    cv::Mat image = cv::imread("../images/road.jpg", 0);
    cv::imshow("Original Image", image);

    cv::Mat sobelX, sobelY, sobel;
    cv::Sobel(image, sobelX, CV_32F, 1, 0);
    cv::Sobel(image, sobelY, CV_32F, 0, 1);
    sobel = cv::abs(sobelX) + cv::abs(sobelY);

    cv::Mat bin1;
    cv::threshold(sobel, bin1, 125, 255, cv::THRESH_BINARY_INV);
    cv::imshow("Sobel (low threshold)", bin1);

    cv::Mat bin2;
    cv::threshold(sobel, bin2, 350, 255, cv::THRESH_BINARY_INV);
    cv::imshow("Sobel (high threshold)", bin2);

    cv::Mat contours;
    cv::Canny(image, contours, 125, 350);
    cv::threshold(contours, contours, 128, 255, cv::THRESH_BINARY_INV);
    cv::imshow("Canny Contours", contours);

    cv::waitKey();
    return 0;
}
