#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <vector>

int main()
{
    cv::Mat src = cv::imread("../resources/girl.jpg");
    cv::imshow("Source", src);
    std::cout << "source size: " << src.size() << std::endl;

    // pyrDown
    cv::Mat dst;
    cv::pyrDown(src, dst);
    cv::imshow("After pyrDown", dst);
    std::cout << "after pyrDown() size: " << dst.size() << std::endl;

    // buildPyramid
    std::vector<cv::Mat> dsts;
    cv::buildPyramid(src, dsts, 3);
    std::cout << "pyramid size: " << dsts.size() << std::endl;
    for (int i = 0; i < dsts.size(); ++i) {
        std::stringstream title;
        title << "Guassian Pyramid #" << i;
        imshow(title.str(), dsts[i]);
        std::cout << title.str() << " size: " << dsts[i].size() << std::endl;
    }

    // compare performance of pyrDown() and resize()
    int64 tick = cv::getTickCount();
    cv::pyrDown(src, dst);
    std::cout << "pyrDown() use " << (cv::getTickCount() - tick) / cv::getTickFrequency()
              << "ms" << std::endl;

    tick = cv::getTickCount();
    cv::resize(src, dst, src.size() / 2);
    std::cout << "resize() use " << (cv::getTickCount() - tick) / cv::getTickFrequency()
              << "ms" << std::endl;

    // pyrUp
    cv::pyrUp(src, dst);
    cv::imshow("After pyrUp", dst);
    std::cout << "after pyrUp() size: " << dst.size() << std::endl;
    
    cv::waitKey();
    return 0;
}
