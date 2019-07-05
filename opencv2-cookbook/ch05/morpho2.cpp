#include "morphoFeatures.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
    cv::Mat image = cv::imread("../images/building.jpg", 0);
    cv::imshow("Image", image);

    MorphoFeatures morpho;
    morpho.setThreshold(40);

    // Get the edges
    cv::Mat edges = morpho.getEdges(image);
    cv::imshow("Edge Image", edges);

    // Get the corners
    cv::Mat corners = morpho.getCorners(image);
    cv::imshow("Corner Image", corners);

    // Display the corner on the image
    morpho.drawOnImage(corners, image);
    cv::imshow("Corners on Image", image);

    image = cv::imread("../images/square.png", 0);
    cv::imshow("Square Image", image);

    // Creating the cross-shaped structuring element
    cv::Mat cross(5, 5, CV_8U, cv::Scalar(0));
    for (int i = 0; i < 5; ++i) {
        cross.at<uchar>(2, i) = 1;
        cross.at<uchar>(i, 2) = 1;
    }

    // Dilate with a cross
    cv::Mat result;
    cv::dilate(image, result, cross);
    cv::imshow("Dilated square with cross", result);

    // Creating the diamond-shaped structuring element
    cv::Mat diamond(5, 5, CV_8U, cv::Scalar(1));
    diamond.at<uchar>(0, 0) = 0;
    diamond.at<uchar>(0, 1) = 0;
    diamond.at<uchar>(1, 0) = 0;
    diamond.at<uchar>(4, 4) = 0;
    diamond.at<uchar>(3, 4) = 0;
    diamond.at<uchar>(4, 3) = 0;
    diamond.at<uchar>(4, 0) = 0;
    diamond.at<uchar>(4, 1) = 0;
    diamond.at<uchar>(3, 0) = 0;
    diamond.at<uchar>(0, 4) = 0;
    diamond.at<uchar>(0, 3) = 0;
    diamond.at<uchar>(1, 4) = 0;

    // Erode with a diamond
    cv::Mat result2;
    cv::erode(result, result2, diamond);
    cv::imshow("Eroded square with diamond", result2);

    // Combine the images into one
    cv::Mat final(100, 300, CV_8U);
    cv::Mat window = final(cv::Rect(0, 0, 100, 100));
    image.copyTo(window);
    window = final(cv::Rect(100, 0, 100, 100));
    result.copyTo(window);
    window = final(cv::Rect(200, 0, 100, 100));
    result2.copyTo(window);
    cv::imshow("Combined", final);

    cv::waitKey();
    return 0;
}
