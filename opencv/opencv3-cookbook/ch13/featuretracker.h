#ifndef FEATURETRACKER_H
#define FEATURETRACKER_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/video/tracking.hpp>

#include <string>
#include <vector>

#include "videoprocessor.h"

class FeatureTracker : public FrameProcessor {

private:
    // current gray-level image
    cv::Mat gray;
    // previous gray-level image
    cv::Mat gray_prev;
    // tracked features from 0->1
    std::vector<cv::Point2f> points[2];
    // initial position of tracked points
    std::vector<cv::Point2f> initial;
    // detected features
    std::vector<cv::Point2f> features;
    // status of tracked features
    std::vector<uchar> status;
    // error in tracking
    std::vector<float> err;

    // maximum number of features to detect
    int max_count;
    // quality level for feature detection
    double qlevel;
    // minimum distance between two feature points
    double minDist;

public:
    FeatureTracker() : max_count(500), qlevel(0.01), minDist(10.0) {}

    void process(cv::Mat &frame, cv::Mat &output)
    {
        cv::cvtColor(frame, gray, CV_BGR2GRAY);
        frame.copyTo(output);

        // 1. if new feature points must be added
        if (addNewPoints()) {
            // detect feature points
            detectFeaturePoints();
            // add the detected features to the currently tracked features
            points[0].insert(points[0].end(), features.begin(), features.end());
            initial.insert(initial.end(), features.begin(), features.end());
        }

        // for first image of the sequence
        if (gray_prev.empty()) {
            gray.copyTo(gray_prev);
        }

        // 2. track features
        cv::calcOpticalFlowPyrLK(gray_prev, gray, // 2 consecutive images
            points[0],  // input point position in first image
            points[1],  // output point position in the second image 
            status,     // tracking success 
            err);       // tracking error

        // 3. loop over the tracked points to reject the undesirables
        int k = 0;
        for (int i = 0; i < points[1].size(); ++i) {
            // do we keep this point?
            if (acceptTrackedPoint(i)) {
                // keep this point in vector
                initial[k] = initial[i];
                points[1][k++] = points[1][i];
            }
        }

        // eliminate unsuccessful points
        points[1].resize(k);
        initial.resize(k);

        // 4. handle the accepted tracked points
        handleTrackedPoints(frame, output);

        // 5. current points and image become previous ones
        points[0] = points[1];
        gray_prev = gray.clone();
    }

    // feature point detection
    void detectFeaturePoints()
    {
        cv::goodFeaturesToTrack(gray, features, max_count, qlevel, minDist);
    }

    // determine if new points should be added
    bool addNewPoints() { return points[0].size() <= 10; }

    // determine which tracked point should be accepted
    // here we keep only moving points
    bool acceptTrackedPoint(int i)
    {
        return status[i] && // status is false if unable to track point i
            // if point has moved
            (abs(points[0][i].x - points[1][i].x) +
             abs(points[0][i].y - points[1][i].y) > 2);
    }

    // handle the currently tracked points
    void handleTrackedPoints(cv::Mat &frame, cv::Mat &output)
    {
        for (int i = 0; i < points[1].size(); ++i) {
            cv::line(output, initial[i], points[1][i], cv::Scalar::all(255));
            cv::circle(output, points[1][i], 3, cv::Scalar::all(255), -1);
        }
    }
};

#endif /* FEATURETRACKER_H */
