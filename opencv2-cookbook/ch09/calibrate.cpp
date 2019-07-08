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

    imshow("Original Image", image);
    imshow("Undistorted Image", uImage);

    cv::waitKey();
    return 0;
}
