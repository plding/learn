#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/bgsegm.hpp>
#include <opencv2/video/background_segm.hpp>

int main()
{
    cv::VideoCapture capture(cv::samples::findFile("bike.avi"));
    if (!capture.isOpened()) {
        return 1;
    }
    
    cv::Mat frame, foreground;

    // The mixture of Gaussian object used with all default parameters
    cv::Ptr<cv::BackgroundSubtractor> MOG = cv::bgsegm::createBackgroundSubtractorMOG();
    // cv::Ptr<cv::BackgroundSubtractorMOG2> MOG = cv::createBackgroundSubtractorMOG2();
    // MOG->setVarThreshold(50);

    bool stop = false;
    while (!stop) {

        if (!capture.read(frame)) {
            break;
        }

        // update the background and return the foreground
        MOG->apply(frame, foreground, 0.01);

        // Complement the image
        cv::threshold(foreground, foreground, 128, 255, cv::THRESH_BINARY_INV);

        // show foreground and background
        cv::imshow("Extracted Foreground", foreground);

        if (cv::waitKey(10) >= 0) {
            stop = true;
        }
    }

    return 0;
}
