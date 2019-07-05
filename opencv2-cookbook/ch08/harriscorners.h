#ifndef HARRISCORNERS
#define HARRISCORNERS

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

class HarrisDetector
{
private:
    // 32-bit float image of corner strength
    cv::Mat cornerStrength;
    // 32-bit float image of thresholded corners
    cv::Mat cornerTh;
    // image of local maxima (internal)
    cv::Mat localMax;
    // size of neighborhood for derivatives smoothing
    int neighborhood;
    // aperture for gradient compulation
    int aperture;
    // Harris parameter
    double k;
    // maximum strength for threshold computation
    double maxStrength;
    // calculated threshold (internal)
    double threshold;
    // size of neighborhood for non-max suppression
    int nonMaxSize;
    // kernel for non-max suppression
    cv::Mat kernel;

public:
    HarrisDetector()
        : neighborhood(3), aperture(3), k(0.1), maxStrength(0.0), threshold(0.01), nonMaxSize(3)
    {
        setLocalMaxWindowSize(nonMaxSize);
    }

    // Create kernel used in non-maxima suppression
    void setLocalMaxWindowSize(int size)
    {
        nonMaxSize = size;
        kernel.create(nonMaxSize, nonMaxSize, CV_8U);
    }

    // Compute Harris corners
    void detect(const cv::Mat &image)
    {
        cv::cornerHarris(image, cornerStrength, neighborhood, aperture, k);

        double minStrength;
        cv::minMaxLoc(cornerStrength, &minStrength, &maxStrength);

        cv::Mat dilated;
        cv::dilate(cornerStrength, dilated, cv::Mat());
        cv::compare(cornerStrength, dilated, localMax, cv::CMP_EQ);
    }

    // Get the corner map from the computed Harris values
    cv::Mat getCornerMap(double qualityLevel)
    {
        cv::Mat cornerMap;

        threshold = qualityLevel * maxStrength;
        cv::threshold(cornerStrength, cornerTh, threshold, 255, cv::THRESH_BINARY);

        cornerTh.convertTo(cornerMap, CV_8U);

        cv::bitwise_and(cornerMap, localMax, cornerMap);

        return cornerMap;
    }

    // Get the feature points vector from the computed Harris values
    void getCorners(std::vector<cv::Point> &points, double qualityLevel)
    {
        getCorners(points, getCornerMap(qualityLevel));
    }

    // Get the feature points vector from the computed corner map
    void getCorners(std::vector<cv::Point> &points, const cv::Mat &cornerMap)
    {
        // Iterate over the pixels to obtain all feature points
        for (int y = 0; y < cornerMap.rows; ++y) {
            const uchar *rowPtr = cornerMap.ptr<uchar>(y);
            for (int x = 0; x < cornerMap.cols; ++x) {
                // if it is a feature point
                if (rowPtr[x]) {
                    points.push_back(cv::Point(x, y));
                }
            }
        }
    }

    // Draw circles at feature point locations on an image
    void drawOnImage(cv::Mat &image, const std::vector<cv::Point> &points,
                     cv::Scalar color = cv::Scalar(255, 255, 255), int radius = 3,
                     int thickness = 2)
    {
        std::vector<cv::Point>::const_iterator it = points.begin();

        while (it != points.end()) {
            cv::circle(image, *it, radius, color, thickness);
            ++it;
        }
    }
};

#endif /* HARRISCORNERS */
