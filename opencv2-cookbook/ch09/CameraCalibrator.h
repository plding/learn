#ifndef CAMERACALIBRATOR_H
#define CAMERACALIBRATOR_H

#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>

class CameraCalibrator
{

private:
    // input points
    std::vector<std::vector<cv::Point3f>> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints;
    // output Matrices
    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;
    // flag to specify how calibration is done
    int flag;
    // used in image undistortion
    cv::Mat map1, map2;
    bool mustInitUndistor;

public:
    CameraCalibrator() : flag(0), mustInitUndistor(true) {};

    // Open the chessboard images and extract corner points
    int addChessboardPoints(const std::vector<std::string> &filelist, cv::Size &boardSize)
    {
        std::vector<cv::Point2f> imageCorners;
        std::vector<cv::Point3f> objectCorners;

        // 3D Scene Points:
        // Initialize the chessbaord corners
        // in the chessboard reference frame
        // The corners are at 3D location (X, Y, Z) = (i, j, 0)
        for (int i = 0; i < boardSize.height; ++i) {
            for (int j = 0; j < boardSize.width; ++j) {
                objectCorners.push_back(cv::Point3f(i, j, 0.0f));
            }
        }

        // 2D Image points:
        cv::Mat image;
        int successes = 0;
        for (int i = 0; i < filelist.size(); ++i) {
            image = cv::imread(filelist[i], 0);
            
            // Get the chessboard corners
            bool found = cv::findChessboardCorners(image, boardSize, imageCorners);

            // Get subpixel accuracy on the corners
            cv::cornerSubPix(image, imageCorners, cv::Size(5, 5), cv::Size(-1, -1),
                             cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 30, 0.1));

            if (imageCorners.size() == boardSize.area()) {
                addPoints(imageCorners, objectCorners);
                successes++;
            }

            cv::drawChessboardCorners(image, boardSize, imageCorners, found);
            cv::imshow("Corners on Chessboard", image);
            cv::waitKey(100);
        }

        return successes;
    }

    // Add scene points and corresponding image points
    void addPoints(const std::vector<cv::Point2f> &imageCorners,
                   const std::vector<cv::Point3f> &objectCorners)
    {
        // 2D image points from one view
        imagePoints.push_back(imageCorners);
        // corresponding 3D scene points
        objectPoints.push_back(objectCorners);
    }

    // Calibrate the camera
    double calibrate(const cv::Size &imageSize)
    {
        // undistorter must be reinitialized
        mustInitUndistor = true;

        // Output rotations and translations
        std::vector<cv::Mat> rvecs, tvecs;

        // start calibration
        return calibrateCamera(objectPoints, // the 3D points
                               imagePoints,  // the image points
                               imageSize,    // image size
                               cameraMatrix, // output camera matrix
                               distCoeffs,   // output distortion matrix
                               rvecs, tvecs, // Rs, Ts
                               flag);        // set options
    }

    // remove distortion in an image (after calibration)
    cv::Mat remap(const cv::Mat &image)
    {
        cv::Mat undistorted;

        if (mustInitUndistor) {
            cv::initUndistortRectifyMap(cameraMatrix,       // computed camera matrix
                                        distCoeffs,         // computed distortion matrix
                                        cv::Mat(),          // optional rectification (none)
                                        cv::Mat(),          // camera matrix to generate undistorted
                                        cv::Size(640, 480), // size of undistorted
                                        CV_32FC1,           // type of output map
                                        map1, map2);        // the x and y mapping functions

            mustInitUndistor = false;
        }

        // Apply mapping functions
        cv::remap(image, undistorted, map1, map2, cv::INTER_LINEAR);

        return undistorted;
    }
};

#endif /* CAMERACALIBRATOR_H */
