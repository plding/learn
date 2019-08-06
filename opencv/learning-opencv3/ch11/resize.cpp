#include <opencv2/opencv.hpp>

void zoomIn(const cv::Mat &image, int type, const char *name)
{
    cv::Mat result;

    int64 tick = cv::getTickCount();
    cv::resize(image, result, cv::Size(0, 0), 4, 4, type);
    std::cout << name << " interpolation use "
              << (cv::getTickCount() - tick) / cv::getTickFrequency()
              << "ms"
              << std::endl;

    cv::imshow(name, result);
}

int main()
{
    cv::Mat image = cv::imread("../resources/girl.jpg");
    cv::imshow("Original Image", image);

    cv::Mat result;

    // 缩小
    cv::resize(image,               // Input image
               result,              // Result image
               image.size() / 2,    // New size
               0,                   // x-rescale
               0,                   // y-rescale
               cv::INTER_LINEAR);   // interpolation method
    cv::imshow("Zoom Out Image", result);

    // 放大
    // new size也可以设置成cv::Size(0, 0), 指定x-rescale和y-rescale设置对应X轴和Y轴的比例因子
    cv::resize(image,               // Input image
               result,              // Result image
               cv::Size(0, 0),      // New Size
               2,                   // x-rescale
               2,                   // y-rescale
               cv::INTER_LINEAR);   // interpolation method

    // 不同插值方法的比较
    zoomIn(image, cv::INTER_NEAREST, "Nearest");    // 最近邻插值
    zoomIn(image, cv::INTER_LINEAR, "Linear");      // 双线性插值
    zoomIn(image, cv::INTER_AREA, "Area");          // 像素区采样插值
    zoomIn(image, cv::INTER_CUBIC, "Cubic");        // 双三次插值
    zoomIn(image, cv::INTER_LANCZOS4, "Lanczos");   // 8x8邻域Lanczos插值

    cv::waitKey();
    return 0;
}
