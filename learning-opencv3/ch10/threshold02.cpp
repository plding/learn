#include <opencv2/opencv.hpp>
#include <vector>

void sum_rgb(const cv::Mat &src, cv::Mat &dst)
{
    std::vector<cv::Mat> planes;
    cv::split(src, planes);

    cv::Mat s = cv::Mat::zeros(src.size(), CV_32F);
    cv::accumulate(planes[0], s);
    cv::accumulate(planes[1], s);
    cv::accumulate(planes[2], s);

    cv::threshold(s, s, 100, 100, cv::THRESH_TRUNC);

    s.convertTo(dst, dst.type());
}

int main()
{
    cv::Mat src = cv::imread("../resources/sunflower.jpg");
    cv::imshow("Original", src);

    cv::Mat dst;
    sum_rgb(src, dst);
    cv::imshow("Result", dst);

    cv::waitKey();
    return 0;
}
