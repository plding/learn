#include <iostream>
using namespace std;

#include "histogram.h"
#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat image = cv::imread("../images/group.jpg", 0);
    if (!image.data)
        return -1;

    cv::imshow("Image", image);

    // The histogram object
    Histogram1D h;

    // Compute the histogram
    cv::MatND histo = h.getHistogram(image);

    // Loop over each bin
    for (int i = 0; i < 256; ++i)
        cout << "Value " << i << " = " << histo.at<float>(i) << endl;

    // Display a histogram as an image
    cv::imshow("Histogram", h.getHistogramImage(image));

    // create a binary image by thresholding at the valley
    cv::Mat thresholded;
    cv::threshold(image, thresholded, 60, 255, cv::THRESH_BINARY);
    cv::imshow("Binary Image", thresholded);

    // Equalize the image
    cv::Mat eq = h.equalize(image);
    cv::imshow("Equalized Image", eq);
    cv::imshow("Equalized Histogram", h.getHistogramImage(eq));

    // Create an image inversion table
    int dims[1] = {256};
    cv::MatND lookup(1, dims, CV_8U);

    for (int i = 0; i < 256; ++i)
        lookup.at<uchar>(i) = 255 - i;

    // Apply lookup and display negative image
    cv::imshow("Negative image", h.applyLookUp(image, lookup));

    // Stretch the image
    cv::Mat stretched = h.stretch(image, 100);
    cv::imshow("Stretched Image", stretched);
    cv::imshow("Stretched Histogram", h.getHistogramImage(stretched));

    cv::waitKey();
    return 0;
}
