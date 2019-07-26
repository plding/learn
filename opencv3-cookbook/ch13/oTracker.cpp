#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking/tracker.hpp>

#include <iostream>
#include <iomanip>

#include "visualTracker.h"

int main()
{
    VideoProcessor processor;

    // Add the image names to be used for tracking
    std::vector<std::string> imgs;
    for (int i = 130; i < 317; ++i) {
        std::ostringstream ss;
        ss << "goose/goose" << std::setfill('0') << std::setw(3) << i << ".bmp"; 

        imgs.push_back(cv::samples::findFile(ss.str()));
    }

    // Create feature tracker instance
    cv::Ptr<cv::TrackerMedianFlow> ptr = cv::TrackerMedianFlow::create();
    VisualTracker tracker(ptr);

    // Specify the original target position
    cv::Rect2d bb(290, 100, 65, 40);
    tracker.setBoundingBox(bb);

    processor.setInput(imgs);
    processor.setFrameProcessor(&tracker);
    processor.displayOutput("Tracked object");
    processor.setDelay(50);
    processor.run();

    return 0;
}
