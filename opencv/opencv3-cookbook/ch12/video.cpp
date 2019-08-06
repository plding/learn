#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <iomanip>

int main()
{
    cv::VideoCapture capture(cv::samples::findFile("bike.avi"));
    if (!capture.isOpened()) {
        return 1;
    }

    double rate = capture.get(cv::CAP_PROP_FPS);
    std::cout << "Frame rate: " << rate << "fps" << std::endl;

    bool stop = false;
    int deplay = 1000 / rate;
    long i = 0;
    cv::Mat frame;

    while (!stop) {
        if (!capture.read(frame)) {
            break;
        }

        cv::imshow("Extracted Frame", frame);

        // std::ostringstream ss;
        // ss << "tmp/bike" << std::setfill('0') << std::setw(3) << i++ << ".bmp";
        // cv::imwrite(ss.str(), frame);

        if (cv::waitKey(deplay) >= 0) {
            stop = true;
        }
    }

    capture.release();

    return 0;
}
