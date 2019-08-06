#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    // Declare Mat type images
    Mat src, gray, thr;

    // Load source iamge, convert it to gray
    src = imread("circle.png", 1);

    // convert image to grayscale 
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // convert grayscale to binary image
    threshold(gray, thr, 100, 255, THRESH_BINARY);

    // find moments of the image
    Moments m = moments(thr, true);
    Point p(m.m10 / m.m00, m.m01 / m.m00);

    // coordinates of centroid
    cout << Mat(p) << endl;

    // show the image with a point mark at the centroid
    circle(src, p, 5, Scalar(128, 0, 0), -1);
    imshow("Image with centroid", src);
    waitKey();

    return 0;
}
