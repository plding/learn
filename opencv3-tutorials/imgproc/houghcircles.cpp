#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    const char *filename = argc >= 2 ? argv[1] : "../data/smarties.png";

    // Loads an image
    Mat src = imread(filename, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Error opening image" << endl;
        cout << "Program Arguments: [image_name -- default " << filename << "]" << endl;
        return -1;
    }

    // Convert to gray
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // reduce noise
    medianBlur(gray, gray, 5);

    // houghcircles
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows / 16, // change this value to detect circles with different distances to each other
                 100, 30, 1, 30  // change the last two parameters
                                 // (min_radius & max_radius) to detect larger circles             
    );
    
    // draw
    for (size_t i = 0; i < circles.size(); ++i) {
        Vec3f c = circles[i];
        Point center = Point(c[0], c[1]);
        circle(src, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
        circle(src, center, c[2], Scalar(255, 0, 255), 3, LINE_AA);
    }

    // display
    imshow("detected circles", src);
    waitKey();

    return 0;
}
