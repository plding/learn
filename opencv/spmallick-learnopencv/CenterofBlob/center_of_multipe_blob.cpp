#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void find_moments(Mat gray);

int main(int argc, char **argv)
{
    // Load source image, convert it to gray
    Mat src, gray;
    src = imread("multiple-blob.png");

    cvtColor(src, gray, COLOR_BGR2GRAY);

    imshow("Source", src);

    find_moments(gray);

    waitKey();
    return 0;
}

void find_moments(Mat gray)
{
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    // Detect edges using canny
    Canny(gray, canny_output, 50, 150, 3);
    // Find contours
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // Get the moments
    vector<Moments> mu(contours.size());
    for (int i = 0; i < contours.size(); ++i) {
        mu[i] = moments(contours[i], false);
    }

    // Get the centroid of figures
    vector<Point2f> mc(contours.size());
    for (int i = 0; i < contours.size(); ++i) {
        mc[i] = Point2f(mu[i].m10/mu[i].m00, mu[i].m01/mu[i].m00);
    }

    // Draw contours
    Mat drawing(canny_output.size(), CV_8UC3, Scalar(255, 255, 255));

    for (int i = 0; i < contours.size(); ++i) {
        Scalar color = Scalar(167, 151, 0);
        drawContours(drawing, contours, i, color, 2, LINE_8, hierarchy);
        circle(drawing, mc[i], 4, color, -1);
    }

    // Show the resultant image
    imshow("Contours", drawing);
    waitKey();
}
