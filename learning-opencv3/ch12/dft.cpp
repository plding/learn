#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

int main()
{
    cv::Mat A = cv::imread("../resources/sunflower.jpg", 0);
    cv::imshow("Original A", A);

    cv::Mat B = A(cv::Rect(A.cols / 2, A.rows / 2, 100, 100));
    cv::imshow("Original B", B);

    int dft_M = cv::getOptimalDFTSize(A.rows + B.rows - 1);
    int dft_N = cv::getOptimalDFTSize(A.cols + B.cols - 1);
    std::cout << "dft_M: " << dft_M << ", dft_N: " << dft_N << std::endl;

    cv::Mat dft_A = cv::Mat::zeros(dft_M, dft_N, CV_32F);
    cv::Mat dft_B = cv::Mat::zeros(dft_M, dft_N, CV_32F);

    cv::Mat dft_A_part = dft_A(cv::Rect(0, 0, A.cols, A.rows));
    cv::Mat dft_B_part = dft_B(cv::Rect(0, 0, B.cols, B.rows));

    A.convertTo(dft_A_part, dft_A_part.type(), 1, -mean(A)[0]);
    B.convertTo(dft_B_part, dft_B_part.type(), 1, -mean(B)[0]);

    cv::dft(dft_A, dft_A, 0, A.rows); 
    cv::dft(dft_B, dft_B, 0, B.rows); 

    cv::mulSpectrums(dft_A, dft_B, dft_A, 0, true);
    cv::idft(dft_A, dft_A, cv::DFT_SCALE, A.rows + B.rows - 1);

    B ^= cv::Scalar::all(255);

    cv::imshow("image", A);
    cv::imshow("ROI", B);

    cv::waitKey();
    return 0;
}
