#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

// using .ptr and []
void colorReduce0(cv::Mat &image, int div = 64)
{
    int nl = image.rows;
    int nc = image.cols * image.channels();

    for (int i = 0; i < nl; ++i) {
        uchar *data = image.ptr<uchar>(i);
        for (int j = 0; j < nc; ++j) {
            data[j] = data[j] / div * div + div / 2;
        }
    }
}

// using .ptr and * ++
void colorReduce1(cv::Mat &image, int div = 64)
{
    int nl = image.rows;
    int nc = image.cols * image.channels();

    for (int i = 0; i < nl; ++i) {
        uchar *data = image.ptr<uchar>(i);
        for (int j = 0; j < nc; ++j) {
            *data++ = *data / div * div + div / 2;
        }
    }
}

// using .ptr and * ++ and modulo
void colorReduce2(cv::Mat &image, int div = 64)
{
    int nl = image.rows;
    int nc = image.cols * image.channels();

    for (int i = 0; i < nl; ++i) {
        uchar *data = image.ptr<uchar>(i);
        for (int j = 0; j < nc; ++j) {
            int v = *data;
            *data++ = v - v % div + div / 2;
        }
    }
}

// using .ptr and * ++ and bitwise
void colorReduce3(cv::Mat &image, int div = 64)
{
    int nl = image.rows;
    int nc = image.cols * image.channels();
    int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
    uchar mask = 0xFF << n;

    for (int i = 0; i < nl; ++i) {
        uchar *data = image.ptr<uchar>(i);
        for (int j = 0; j < nc; ++j) {
            *data++ = *data & mask + div / 2;
        }
    }
}

// direct pointer arithmetic
void colorReduce4(cv::Mat &image, int div = 64)
{
    int nl = image.rows;
    int nc = image.cols * image.channels();
    int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
    int step = image.step;
    uchar mask = 0xFF << n;

    uchar *data = image.data;

    for (int i = 0; i < nl; ++i) {
        for (int j = 0; j < nc; ++j) {
            *(data + j) = *data & mask + div / 2;
        }
        data += step;
    }
}

// using .ptr and * ++ and bitwise with image.cols * image.channels()
void colorReduce5(cv::Mat &image, int div = 64)
{
    int nl = image.rows;
    int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
    uchar mask = 0xFF << n;

    for (int i = 0; i < nl; ++i) {
        uchar *data = image.ptr<uchar>(i);
        for (int j = 0; j < image.cols * image.channels(); ++j) {
            *data++ = *data / div * div + div / 2;
        }
    }
}

#define NTESTS 6
#define NITERATIONS 20

int main()
{
    int64 t[NTESTS], tinit;
    cv::Mat image1;

    // timer values set to 0
    for (int i = 0; i < NTESTS; ++i)
        t[i] = 0;

    // repeat the tests several times
    int n = NITERATIONS;
    for (int k = 0; k < n; ++k) {
        std::cout << k << " of " << n << std::endl;

        image1 = cv::imread("../images/image.jpg");
        if (!image1.data) {
            return -1;
        }

        // using .ptr and []
        tinit = cv::getTickCount();
        colorReduce0(image1);
        t[0] += cv::getTickCount() - tinit;

        image1 = cv::imread("../images/image.jpg");
        // using .ptr and * ++
        tinit = cv::getTickCount();
        colorReduce1(image1);
        t[1] += cv::getTickCount() - tinit;

        image1 = cv::imread("../images/image.jpg");
        // using .ptr and * ++ and modulo
        tinit = cv::getTickCount();
        colorReduce2(image1);
        t[2] += cv::getTickCount() - tinit;

        image1 = cv::imread("../images/image.jpg");
        // using .ptr and * ++ and bitwise
        tinit = cv::getTickCount();
        colorReduce3(image1);
        t[3] += cv::getTickCount() - tinit;

        image1 = cv::imread("../images/image.jpg");
        // using direct pointer arithmetic
        tinit = cv::getTickCount();
        colorReduce4(image1);
        t[4] += cv::getTickCount() - tinit;

        image1 = cv::imread("../images/image.jpg");
        // using .ptr and * ++ and bitwise with image.cols * image.channels()
        tinit = cv::getTickCount();
        colorReduce5(image1);
        t[5] += cv::getTickCount() - tinit;
    }

    cv::namedWindow("Image Result");
    cv::imshow("Image Result", image1);

    // print average execution time
    std::cout << std::endl
              << "--------------------------------------------" << std::endl
              << std::endl;
    std::cout << "using .ptr and [] =" << 1000. * t[0] / cv::getTickFrequency() / n << "ms"
              << std::endl;
    std::cout << "using .ptr and * ++ =" << 1000. * t[1] / cv::getTickFrequency() / n << "ms"
              << std::endl;
    std::cout << "using .ptr and * ++ and modulo =" << 1000. * t[2] / cv::getTickFrequency() / n
              << "ms" << std::endl;
    std::cout << "using .ptr and * ++ and bitwise =" << 1000. * t[3] / cv::getTickFrequency() / n
              << "ms" << std::endl;
    std::cout << "using direct pointer arithmetic =" << 1000. * t[4] / cv::getTickFrequency() / n
              << "ms" << std::endl;
    std::cout << "using .ptr and * ++ and bitwise with image.cols * image.channels()  ="
              << 1000. * t[5] / cv::getTickFrequency() / n << "ms" << std::endl;

    cv::waitKey();
    return 0;
}
