#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
    cv::Mat image = cv::imread("../resources/boldt.jpg", 0);
    cv::imshow("Original Image", image);

    cv::Mat edges;
    cv::Canny(image,    // Input single channel image
              edges,    // Output edge image
              150,      // lower threshold
              300,      // high threshold
              3,        // Sobel aperture
              false);   // true=L2-norm (more accurate)

    imshow("Canny Edges", edges);

    cv::waitKey();
    return 0;
}
