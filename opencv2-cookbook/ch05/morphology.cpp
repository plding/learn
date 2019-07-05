#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
    cv::Mat image = cv::imread("../images/binary.bmp");
    if (!image.data)
        return -1;

    cv::imshow("Image", image);

    // Erode the image
    cv::Mat eroded;
    cv::erode(image, eroded, cv::Mat());
    cv::imshow("Eroded Image", eroded);

    // Dilate the image
    cv::Mat dilated;
    cv::dilate(image, dilated, cv::Mat());
    cv::imshow("Dilated Image", dilated);

    // Erode the image with a larger s.e.
    cv::Mat element(7, 7, CV_8U, cv::Scalar(1));
    cv::erode(image, eroded, element);
    cv::imshow("Eroded Image (7x7)", eroded);

    // Erode the image 3 times.
    cv::erode(image, eroded, cv::Mat(), cv::Point(-1, -1), 3);
    cv::imshow("Eroded Image (3 times)", eroded);

    // Close the image
    cv::Mat element5(5, 5, CV_8U, cv::Scalar(1));
    cv::Mat closed;
    cv::morphologyEx(image, closed, cv::MORPH_CLOSE, element5);
    cv::imshow("Closed Image", closed);

    // Open the image
    cv::Mat opened;
    cv::morphologyEx(image, opened, cv::MORPH_OPEN, element5);
    cv::imshow("Opened Image", opened);

    // Close and Open the image
    cv::morphologyEx(image, image, cv::MORPH_CLOSE, element5);
    cv::morphologyEx(image, image, cv::MORPH_OPEN, element5);
    cv::imshow("Closed and Opened Image", image);

    image = cv::imread("../images/binary.bmp");

    // Open and Close the image
    cv::morphologyEx(image, image, cv::MORPH_OPEN, element5);
    cv::morphologyEx(image, image, cv::MORPH_CLOSE, element5);
    cv::imshow("Opened and Closed Image", image);

    cv::waitKey();
    return 0;
}
