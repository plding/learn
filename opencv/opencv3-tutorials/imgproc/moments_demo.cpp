#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

Mat src_gray;
int thresh = 100;
RNG rng(12345);

void thresh_callback(int, void *);

int main(int argc, char **argv)
{
    // Load source image
    CommandLineParser parser(argc, argv, "{@input | ../data/stuff.jpg | input image}");    
    Mat src = imread(parser.get<String>("@input"));
    if (src.empty()) {
        cout << "Could not open or find the image!\n" << endl;
        parser.printMessage();
        return -1;
    }

    // convert image to gray and blur it
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));

    // Create window
    const char *source_window = "Source";
    imshow(source_window, src);

    // Create trackbar
    const int max_thresh = 255;
    createTrackbar("Canny thresh:", source_window, &thresh, max_thresh, thresh_callback);
    thresh_callback(0, 0);

    waitKey();
    return 0;
}

void thresh_callback(int, void *)
{
    // Detect edges using Canny
    Mat canny_output;
    Canny(src_gray, canny_output, thresh, thresh * 2);

    // Find contours
    vector<vector<Point> > contours;
    findContours(canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // Get the moments
    vector<Moments> mu(contours.size());
    for (size_t i = 0; i < contours.size(); ++i) {
        mu[i] = moments(contours[i]);
    }

    // Get the mass centers
    vector<Point2f> mc(contours.size());
    for (size_t i = 0; i < contours.size(); ++i) {
        // add 1e-5 to avoid division by zero
        mc[i] = Point2f(static_cast<float>(mu[i].m10 / (mu[i].m00 + 1e-5)),
                        static_cast<float>(mu[i].m01 / (mu[i].m00 + 1e-5)));
        cout << "mc[" << i << "]" << mc[i] << endl; 
    }

    // Draw contours
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); ++i) {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours, (int) i, color, 2);
        circle(drawing, mc[i], 4, color, -1);
    }

    // Show in a window
    imshow("Contours", drawing);
}
