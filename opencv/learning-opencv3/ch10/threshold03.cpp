#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat image = cv::imread("../resources/sunflower.jpg", 0);
    cv::imshow("Original Image", image);

    cv::Mat thresholded;
    cv::adaptiveThreshold(image, thresholded, 255, cv::ADAPTIVE_THRESH_MEAN_C,
                          cv::THRESH_BINARY, 71, 15);
    cv::imshow("mean adaptive threshold Image", thresholded);

    cv::adaptiveThreshold(image, thresholded, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C,
                          cv::THRESH_BINARY, 71, 15);
    cv::imshow("gaussian adaptive threshold Image", thresholded);

    cv::waitKey();
    return 0;
}
