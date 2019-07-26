#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

#include <iostream>

#include "harrisDetector.h"

int main()
{
    // Read Input image
    cv::Mat image = cv::imread(cv::samples::findFile("church01.jpg"), 0);
    if (image.empty()) {
        std::cerr << "Could not open or find the image!\n" << std::endl;
        return 1;
    }

    // rotate the image (to produce a horizontal image)
    cv::transpose(image, image);
    cv::flip(image, image, 0);
    cv::imshow("Original", image);

    //--- Harris
    cv::Mat cornerStrength;

    // Detect Harris corners
    cv::cornerHarris(
        image,          // Input single-channel 8-bit or floating-point image
        cornerStrength, // Image to store the Harris detector responses. It has the type
                        // CV_32FC1 and the same size as src
        3,              // Neighborhood size
        3,              // Aperture parameter for the Sobel operator
        0.01            // Harris detector free parameter
    );

    // threshold the corner strengths
    cv::Mat harrisCorners;
    cv::threshold(cornerStrength, harrisCorners, 0.0001, 255, cv::THRESH_BINARY_INV);
    cv::imshow("Harris", harrisCorners);

    // Create Harris detector instance
    HarrisDetector harris;
    harris.detect(image);

    // Detect Harris corners
    std::vector<cv::Point> pts;
    harris.getCorners(pts, 0.02);

    // Draw Harris corners
    cv::Mat output = image.clone();
    harris.drawOnImage(output, pts);
    cv::imshow("Corners", output);

    //--- GFTT
    cv::Ptr<cv::GFTTDetector> gftt = cv::GFTTDetector::create(
        500,    // maximum number of keypoints to be returned
        0.01,   // quality level
        10      // minum allowed distance between points
    );

    // Compute good features to track
    std::vector<cv::KeyPoint> keypoints;
    gftt->detect(image, keypoints);

    output = image.clone();
    cv::drawKeypoints(image, keypoints, output, cv::Scalar::all(255),
                      cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);
    cv::imshow("Good Features to Track Detector", output);

    //--- FAST Feature
    cv::Ptr<cv::FastFeatureDetector> fast = cv::FastFeatureDetector::create(40);
    fast->detect(image, keypoints);

    output = image.clone();
    cv::drawKeypoints(image, keypoints, output, cv::Scalar::all(255),
                      cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);
    cv::imshow("FAST", output);

    //--- Fast Feature detect use grid
    int total = 100;
    int hstep = 5, vstep = 3;
    int hsize = image.cols / hstep, vsize = image.rows / vstep;
    int subtotal = total / (hstep * vstep);
    std::cout << "Grid of " << vstep << " by " << hstep << " each of size "
              << vsize << " by " << hsize << std::endl;
    
    // detection with low threshold
    fast->setThreshold(20);

    // detect on each grid
    keypoints.clear();
    for (int i = 0; i < vstep; ++i) {
        for (int j = 0; j < hstep; ++j) {
            // create ROI over current grid 
            cv::Mat imageROI = image(cv::Rect(j * hsize, i * vsize, hsize, vsize));
            
            // detect the keypoints in grid
            std::vector<cv::KeyPoint> gridpoints;
            fast->detect(imageROI, gridpoints);
            std::cout << "Number of FAST in grid " << i << "," << j << ": " << gridpoints.size() << std::endl; 

            // get the strongest FAST features
            auto itEnd(gridpoints.end());
            if (gridpoints.size() > subtotal) {
                std::nth_element(gridpoints.begin(), gridpoints.begin() + subtotal, itEnd,
                        [](cv::KeyPoint &a, cv::KeyPoint &b) { return a.response > b.response; });
                itEnd = gridpoints.begin() + subtotal;
            }

            // add them to the global keypoint vector
            for (auto it = gridpoints.begin(); it != itEnd; ++it) {
                it->pt += cv::Point2f(j * hsize, i * vsize);
                keypoints.push_back(*it);
            }
        }
    }

    // draw the keypoints
    output = image.clone();
    cv::drawKeypoints(image, keypoints, output, cv::Scalar::all(255),
                      cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);
    cv::imshow("FAST Features (grid)", output);

    //--- SURF 
    cv::Ptr<cv::xfeatures2d::SurfFeatureDetector> surf = cv::xfeatures2d::SurfFeatureDetector::create(2000.0);
    surf->detect(image, keypoints);

    output = image.clone();
    cv::drawKeypoints(image, keypoints, output, cv::Scalar::all(255),
                      cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imshow("SURF", output);

    cv::waitKey();
    return 0;
}
