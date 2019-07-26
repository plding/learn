#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking/tracker.hpp>

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>

#include "visualTracker.h"

int main()
{
    VideoProcessor processor;

    std::vector<std::string> images;
    for (int i = 130; i < 317; ++i) {
        std::ostringstream ss;
        ss << "goose/goose" << std::setfill('0') << std::setw(3) << i << ".bmp";
        images.push_back(cv::samples::findFile(ss.str()));
    }

    VisualTracker tracker(cv::TrackerKCF::create());

    cv::Rect2d box(290, 100, 65, 40);
    tracker.setBoundingBox(box);

    processor.setInput(images);
    processor.setFrameProcessor(&tracker);
    processor.displayOutput("Tracked object");
    processor.setDelay(50);
    processor.run();

    return 0;
}
