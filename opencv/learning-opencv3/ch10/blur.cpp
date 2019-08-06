#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat image = cv::imread("../resources/boldt.jpg");
    cv::imshow("Original Image", image);

    cv::Mat blured;

    // box filter
    cv::boxFilter(image,                    // Input image
                  blured,                   // Result image
                  -1,                       // Output depth
                  cv::Size(3, 3),           // Kernel size
                  cv::Point(-1, -1),        // Location of anchor point
                  true,                     // Normalize, if true, divide by box area
                  cv::BORDER_DEFAULT);      // Border extrapolation to use
    cv::imshow("boxFilter result", blured);

    // blur
    cv::blur(image,                         // Input image
             blured,                        // Result image
             cv::Size(3, 3),                // Kernel size
             cv::Point(-1, -1),             // Location of anchor point
             cv::BORDER_DEFAULT);           // Border extrapolation to use
    cv::imshow("blur result", blured);

    // median blur
    cv::medianBlur(image,                   // Input image
                   blured,                  // Result image
                   3);                      // Kernel size
    cv::imshow("medianBlur result", blured);

    // gaussian blur
    cv::GaussianBlur(image,                 // Input image
                     blured,                // Result image
                     cv::Size(3, 3),        // Kernel size
                     0.0,                   // Guassian half-width in x-direction
                     0.0,                   // Guassian half-width in y-direction
                     cv::BORDER_DEFAULT);   // Border extrapolation to use
    cv::imshow("GuassianBlur result", blured);

    // bilateral filter
    cv::bilateralFilter(image,              // Input image
                        blured,             // Result image
                        3,                  // Pixel neighborhoold size (max distance)
                        0.0,                // Width param for color weight function
                        0.0,                // Width param for spatial weight function
                        cv::BORDER_DEFAULT);// Border extrapolation to use
    cv::imshow("bilateralFilter result", blured);

    cv::waitKey();
    return 0;
}
