#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

void sharpen(const cv::Mat &image, cv::Mat &result)
{
    for (int i = 1; i < image.rows - 1; ++i) {
        // for all rows (except first and last)
       const uchar *previous = image.ptr<const uchar>(i - 1); // previous row
       const uchar *current  = image.ptr<const uchar>(i);     // current row
       const uchar *next     = image.ptr<const uchar>(i + 1); // next row

       uchar *output = result.ptr<uchar>(i);

       for (int j = 1; j < image.cols - 1; ++j) {
           *output++ = cv::saturate_cast<uchar>(5 * current[j] - current[j-1] - current[j+1] -
                                                previous[j] - next[j]);
       } 
    }

    // set the unprocess pixels to 0
    result.row(0).setTo(cv::Scalar(0));
    result.row(result.rows - 1).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.col(result.cols - 1).setTo(cv::Scalar(0));
}

void sharpen2(const cv::Mat &image, cv::Mat &result)
{
    int step = image.step1();
    const uchar *previous = image.data;
    const uchar *current  = image.data + step;
    const uchar *next     = image.data + 2 * step;
    uchar *output         = result.data + step;

    for (int i = 1; i < image.rows - 1; ++i) {
        // for each row (except first and last)
        for (int j = 1; j < image.cols - 1; ++j) {
            // for each column (except first and last)
            output[j] = cv::saturate_cast<uchar>(5 * current[j] - current[j-1] - current[j+1] -
                                                 previous[j] - next[j]);
        }

        previous += step;
        current  += step;
        next     += step;
        output   += step;
    }

    result.row(0).setTo(cv::Scalar(0));
    result.row(result.rows - 1).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.col(result.cols - 1).setTo(cv::Scalar(0));
}

void sharpen3(const cv::Mat &image, cv::Mat &result)
{
    auto it     = image.begin<uchar>() + image.step;
    auto itend  = image.end<uchar>() - image.step;
    auto itup   = image.begin<uchar>();
    auto itdown = image.begin<uchar>() + 2 * image.step;
    auto itout  = result.begin<uchar>() + result.step;

    for (; it != itend; ++it, ++itup, ++itdown)
        *itout = cv::saturate_cast<uchar>(*it * 5 - *(it - 1) - *(it + 1) - *itup - *itdown);
}

void sharpen2D(const cv::Mat &image, cv::Mat &result)
{
    // Construct kernel (all entries initialized to 0)
    cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0));
    // assigns kernel values
    kernel.at<float>(1, 1) = 5.0;
    kernel.at<float>(0, 1) = -1.0;
    kernel.at<float>(2, 1) = -1.0;
    kernel.at<float>(1, 0) = -1.0;
    kernel.at<float>(1, 2) = -1.0;

    // filter the image
    cv::filter2D(image, result, image.depth(), kernel);
}

int main()
{
    cv::Mat image = cv::imread("../images/boldt.jpg", 0);
    if (!image.data) {
        return -1;
    }

    cv::imshow("Original Image", image);

    cv::Mat result;
    result.create(image.size(), image.type());

    double time = static_cast<double>(cv::getTickCount());
    sharpen(image, result);
    time = (static_cast<double>(cv::getTickCount()) - time) / cv::getTickFrequency();
    std::cout << "time= " << time << std::endl;
    cv::namedWindow("Image");
    cv::imshow("Image", result);
    
    time = static_cast<double>(cv::getTickCount());
    sharpen2(image, result);
    time = (static_cast<double>(cv::getTickCount()) - time) / cv::getTickFrequency();
    std::cout << "time= " << time << std::endl;
    cv::namedWindow("Image 2");
    cv::imshow("Image 2", result);

    time = static_cast<double>(cv::getTickCount());
    sharpen3(image, result);
    time = (static_cast<double>(cv::getTickCount()) - time) / cv::getTickFrequency();
    std::cout << "time= " << time << std::endl;
    cv::namedWindow("Image 3");
    cv::imshow("Image 3", result);

    time = static_cast<double>(cv::getTickCount());
    sharpen2D(image, result);
    time = (static_cast<double>(cv::getTickCount()) - time) / cv::getTickFrequency();
    std::cout << "time= " << time << std::endl;
    cv::namedWindow("Image 2D2D");
    cv::imshow("Image 2D", result);

    cv::waitKey();
    return 0;
}
