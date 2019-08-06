#ifndef HARRIS_DETECTOR_H
#define HARRIS_DETECTOR_H

class HarrisDetector {

private:
    // 32-bit float image of corner strength
    cv::Mat cornerStrength;
    // image of local maxima
    cv::Mat localMax;
    // size of neighborhood for derivatives smoothing
    int neighborhood;
    // aperture for gradident computation
    int aperture;
    // Harris parameter
    double k;
    // maximum strength for threshold computation
    double maxStrength;
    // size of neighborhood for non-max suppression
    int nonMaxSize;
    // kernel for non-max suppression
    cv::Mat kernel;

public:
    HarrisDetector() : neighborhood(3), aperture(3), k(0.1), maxStrength(0.0), nonMaxSize(3)
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
        // Harris computation
        cv::cornerHarris(image, cornerStrength, neighborhood, aperture, k);

        // internal threshold computation
        cv::minMaxLoc(cornerStrength, NULL, &maxStrength);

        // local maxima detection
        cv::Mat dilated;
        cv::dilate(cornerStrength, dilated, cv::Mat());
        cv::compare(cornerStrength, dilated, localMax, cv::CMP_EQ);
    }

    // Get the feature points vector from the computed Harris values
    void getCorners(std::vector<cv::Point> &points, double qualityLevel)
    {
        cv::Mat cornerMap;

        // thresholding the corner strength
        double threshold = qualityLevel * maxStrength;
        cv::threshold(cornerStrength, cornerMap, threshold, 255, cv::THRESH_BINARY);

        // convert to 8-bit image
        cornerMap.convertTo(cornerMap, CV_8U);

        // non-maxima suppression
        cv::bitwise_and(cornerMap, localMax, cornerMap);

        // Iterate over the pixels to obtain all feature points
        for (int y = 0; y < cornerMap.rows; ++y) {
            const uchar *rowPtr = cornerMap.ptr<uchar>(y);
            for (int x = 0; x < cornerMap.cols; ++x) {
                if (rowPtr[x]) {
                    points.push_back(cv::Point(x, y));
                }
            }
        }
    }

    // Draw circles at feature point locations on an image
    void drawOnImage(cv::Mat &image, const std::vector<cv::Point> &points,
                     cv::Scalar color = cv::Scalar::all(255), int radius = 3,
                     int thickness = 1)
    {
        std::vector<cv::Point>::const_iterator it = points.begin();

        while (it != points.end()) {
            cv::circle(image, *it, radius, color, thickness);
            ++it;
        }
    }
};

#endif /* HARRIS_DETECTOR_H */
