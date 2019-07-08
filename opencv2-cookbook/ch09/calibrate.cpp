#include <iomanip>
#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "CameraCalibrator.h"

int main()
{
    cv::Mat image;
    std::vector<std::string> filelist;

    for (int i = 1; i <= 20; ++i) {
        std::stringstream str;
        str << "../images/chessboards/chessboard" << std::setw(2) << std::setfill('0') << i
            << ".jpg";
        std::cout << str.str() << std::endl;

        filelist.push_back(str.str());
        image = cv::imread(str.str(), 0);
        cv::imshow("Image", image);

        cv::waitKey(100);
    }

    CameraCalibrator cameraCalibrator;
    cv::Size boardSize(6, 4);
    cameraCalibrator.addChessboardPoints(filelist, boardSize);
    cameraCalibrator.calibrate(image.size());

    image = cv::imread(filelist[6]);
    cv::Mat uImage = cameraCalibrator.remap(image);

    // display camera matrix
    cv::Mat cameraMatrix = cameraCalibrator.getCameraMatrix();
    std::cout << " Camera intrinsic: " << cameraMatrix.rows << "x" << cameraMatrix.cols
              << std::endl;
    std::cout << cameraMatrix.at<double>(0, 0) << " " << cameraMatrix.at<double>(0, 1) << " "
              << cameraMatrix.at<double>(0, 2) << std::endl;
    std::cout << cameraMatrix.at<double>(1, 0) << " " << cameraMatrix.at<double>(1, 1) << " "
              << cameraMatrix.at<double>(1, 2) << std::endl;
    std::cout << cameraMatrix.at<double>(2, 0) << " " << cameraMatrix.at<double>(2, 1) << " "
              << cameraMatrix.at<double>(2, 2) << std::endl;

    imshow("Original Image", image);
    imshow("Undistorted Image", uImage);

    cv::waitKey();
    return 0;
}
