#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <video_path>" << std::endl;
        return -1;
    }

    cv::VideoCapture cap;
    cap.open(std::string(argv[1]));

    cv::Mat frame;
    for ( ; ; ) {
        cap >> frame;
        if (frame.empty()) break;

        cv::imshow("Video Frame", frame);

        if ((char) cv::waitKey(33) >= 0) break;
    }

    return 0;
}
