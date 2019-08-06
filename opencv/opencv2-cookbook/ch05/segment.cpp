#include "watershedSegmentation.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
    cv::Mat image = cv::imread("../images/group.jpg");
    cv::imshow("Original Image", image);

    cv::Mat binary = cv::imread("../images/binary.bmp", 0);
    cv::imshow("Binary Image", binary);

    cv::Mat fg;
    cv::erode(binary, fg, cv::Mat(), cv::Point(-1, -1), 6);
    cv::imshow("Foreground Image", fg);

    cv::Mat bg;
    cv::dilate(binary, bg, cv::Mat(), cv::Point(-1, -1), 6);
    cv::threshold(bg, bg, 1, 128,cv::THRESH_BINARY_INV);
    cv::imshow("Background Image", bg);

    cv::Mat markers/*(binary.size(), CV_8U, cv::Scalar(0))*/;
    markers = fg + bg;
    cv::imshow("Markers", markers);

    WatershedSegmenter segmenter;
    segmenter.setMarkers(markers);
    segmenter.process(image);
    cv::imshow("Segmentation", segmenter.getSegmentation());
    cv::imshow("Watersheds", segmenter.getWatersheds());

    image = cv::imread("../images/tower.jpg");

    cv::Mat imageMask(image.size(), CV_8U, cv::Scalar(0));
    cv::rectangle(imageMask, cv::Point(5, 5), cv::Point(image.cols - 5, image.rows - 5),
                 cv::Scalar(255), 3);
    cv::rectangle(imageMask, cv::Point(image.cols / 2 - 10, image.rows / 2 - 10),
                  cv::Point(image.cols / 2 + 10, image.rows / 2 + 10), cv::Scalar(128), 10);

    segmenter.setMarkers(imageMask);
    segmenter.process(image);

    cv::rectangle(image, cv::Point(5, 5), cv::Point(image.cols - 5, image.rows - 5),
                 cv::Scalar(255, 255, 255), 3);
    cv::rectangle(image, cv::Point(image.cols / 2 - 10, image.rows / 2 - 10),
                  cv::Point(image.cols / 2 + 10, image.rows / 2 + 10), cv::Scalar(1, 1, 1), 10);
    cv::imshow("Image with marker", image);
    cv::imshow("Watersheds of foreground object", segmenter.getWatersheds());

    image = cv::imread("../images/tower.jpg");
    cv::Rect rectangle(50, 70, image.cols - 150, image.rows - 180);

    cv::Mat result, bgModel, fgModel;
    cv::grabCut(image, result, rectangle, bgModel, fgModel, 1, cv::GC_INIT_WITH_RECT);
    cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
    cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));
    image.copyTo(foreground, result);
    cv::rectangle(image, rectangle, cv::Scalar(255, 255, 255), 1);
    cv::imshow("Image", image);
    cv::imshow("Segmented Image", foreground);

    image = cv::imread("../images/group.jpg");
    cv::Rect rectangle2(10, 100, 380, 180);

    cv::Mat bkgModel, fgrModel;
    cv::grabCut(image, result, rectangle2, bkgModel, fgrModel, 5, cv::GC_INIT_WITH_RECT);

    result = result & 1;
    foreground.create(image.size(), CV_8UC3);
    foreground.setTo(cv::Scalar(255, 255, 255));
    image.copyTo(foreground, result);

    cv::rectangle(image, rectangle2, cv::Scalar(255, 255, 255), 1);
    cv::imshow("Image 2", image);
    cv::imshow("Foreground objects", foreground);

    cv::waitKey();
    return 0;
}
