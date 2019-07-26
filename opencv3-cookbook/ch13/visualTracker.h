#ifndef VISUALTRACKER_H
#define VISUALTRACKER_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/tracking/tracker.hpp>

#include <string>
#include <vector>

#include "videoprocessor.h"

class VisualTracker : public FrameProcessor {

private:
    cv::Ptr<cv::Tracker> tracker;
    cv::Rect2d box;
    bool reset;

public:
    VisualTracker(cv::Ptr<cv::Tracker> tracker) : reset(true), tracker(tracker) {}

    void setBoundingBox(cv::Rect2d &bb)
    {
       box = bb; 
       reset = true;
    }

    void process(cv::Mat &frame, cv::Mat &output)
    {
        if (reset) {
            reset = false;
            tracker->init(frame, box);
        } else {
            tracker->update(frame, box);
        }

        frame.copyTo(output);
        cv::rectangle(output, box, cv::Scalar::all(255), 2);
    }
};

#endif /* VISUALTRACKER_H */
