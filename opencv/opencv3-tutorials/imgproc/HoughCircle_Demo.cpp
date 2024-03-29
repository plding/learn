#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

namespace
{
    // windows and trackbars name
    const string windowName = "Hough Circle Detection Demo";
    const string cannyThresholdTrackbarName = "Canny Threshold";
    const string accumulatorThresholdTrackbarName = "Accumulator Threshold";
    const string usage = "Usage: tutorial_HoughCircle_Demo <path_to_input_image>\n";

    // initial and max values of the parameters of interests. 
    const int cannyThresholdInitialValue = 100;
    const int accumulatorThresholdInitialValue = 50;
    const int maxAccumulatorThreshold = 200;
    const int maxCannyThreshold = 255;

    void HoughDetection(const Mat &src_gray, const Mat &src_display, int cannyThreshold, int accumulatorThreshold)
    {
        // will hold the results of the detection
        vector<Vec3f> circles;
        // runs the actual detection
        HoughCircles(src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows / 8, cannyThreshold, accumulatorThreshold, 0, 0);

        // clone the colour, input image for displaying purposes
        Mat display = src_display.clone();
        for (size_t i = 0; i < circles.size(); ++i) {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            // circle center
            circle(display, center, 3, Scalar(0, 255, 0), -1, 8, 0);
            // circle outline
            circle(display, center, radius, Scalar(0, 0, 255), 3, 8, 0);
        }

        // shows the results
        imshow(windowName, display);
    }
}

int main(int argc, char **argv)
{
    Mat src, src_gray;

    // Read the image
    String imageName("../data/stuff.jpg");
    if (argc > 1) {
        imageName = argv[1];
    }
    
    src = imread(imageName, IMREAD_COLOR);
    if (src.empty()) {
        cerr << "Invalid input image" << endl;
        return -1;
    }

    // Convert it to gray
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    // Reduce the noise so we avoid false circle detection
    GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

    // declare and initialize both parameters that are subjects to change
    int cannyThreshold = cannyThresholdInitialValue;
    int accumulatorThreshold = accumulatorThresholdInitialValue;

    // create the main window, and attach the trackbars
    namedWindow(windowName, WINDOW_AUTOSIZE);
    createTrackbar(cannyThresholdTrackbarName, windowName, &cannyThreshold, maxCannyThreshold);
    createTrackbar(accumulatorThresholdTrackbarName, windowName, &accumulatorThreshold, maxAccumulatorThreshold);

    // infinite loop to display
    // and refresh the content of the output image
    // until the user presses q or Q
    char key = 0;
    while (key != 'q' && key != 'Q') {
        // those parameters cannot be =0
        // so we must check here
        cannyThreshold = max(cannyThreshold, 1);
        accumulatorThreshold = max(accumulatorThreshold, 1);

        // runs the detection, and update the display
        HoughDetection(src_gray, src, cannyThreshold, accumulatorThreshold);

        // get user key
        key = (char) waitKey(10);
    }

    return 0;
}
