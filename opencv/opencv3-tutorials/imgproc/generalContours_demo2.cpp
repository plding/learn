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

    // Convert image to gray and blur it
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

    // Find the rotated rectangles and ellipses for each contour
    vector<RotatedRect> minRect(contours.size());
    vector<RotatedRect> minEllipse(contours.size());
    for (size_t i = 0; i < contours.size(); ++i) {
        minRect[i] = minAreaRect(contours[i]);
        if (contours[i].size() > 5) {
            minEllipse[i] = fitEllipse(contours[i]);
        }
    }

    // Draw contours + rotated rects + ellipses
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); ++i) {
        Scalar color(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        // contour
        drawContours(drawing, contours, (int) i, color);
        // ellipse
        ellipse(drawing, minEllipse[i], color, 2);
        // rotated rectangle
        Point2f rect_points[4];
        minRect[i].points(rect_points);
        for (int j = 0; j < 4; ++j) {
            line(drawing, rect_points[j], rect_points[(j+1)%4], color);
        }
    }

    // Show in a image
    imshow("Contours", drawing);
}
