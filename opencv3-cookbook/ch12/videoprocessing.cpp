#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

#include "videoprocessor.h"

// processing function
void canny(cv::Mat &img, cv::Mat &out)
{
    if (img.channels() == 3) {
        cv::cvtColor(img, out, cv::COLOR_BGR2GRAY);
    } else {
        out = img.clone();
    }

    cv::Canny(out, out, 100, 200);
    cv::threshold(out, out, 128, 255, cv::THRESH_BINARY_INV);
}

int main()
{
    VideoProcessor processor;

    // Open video file
    processor.setInput(cv::samples::findFile("bike.avi"));

    // Declare a window to display the video
    processor.displayInput("Input Video");
    processor.displayOutput("Output Video");

    // Play the video at the original frame rate
    processor.setDelay(1000.0 / processor.getFrameRate());

    // Set the frame processor callback function
    processor.setFrameProcessor(canny);

    // Output a video
    processor.setOutput("tmp/bikeCanny.avi");

    // // Stop the process at this frame
    // processor.stopAtFrameNo(51);

    // Start the process
    processor.run();

    return 0;
}
