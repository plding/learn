#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat dst, cdst, cdstP;

    const char *default_file = "../data/sudoku.png";
    const char *filename = argc >= 2 ? argv[1] : default_file;

    // Load an image
    Mat src = imread(filename, IMREAD_GRAYSCALE);
    if (src.empty()) {
        cout << "Error opening image" << endl;
        cout << "Program Arguments: [image_name -- default " << default_file << "]" << endl;
        return -1;
    }

    // Edge detection
    Canny(src, dst, 50, 200, 3);

    // Copy edges to the images that will display the results in BGR
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    cdstP = cdst.clone();

    // Standard Hough Line Transform
    vector<Vec2f> lines;
    HoughLines(dst, lines, 1, CV_PI / 180, 150, 0, 0);
    for (size_t i = 0; i < lines.size(); ++i) {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
    }

    // Probabilistic Line Transform
    vector<Vec4i> linesP;
    HoughLinesP(dst, linesP, 1, CV_PI / 180, 50, 50, 10);
    for (size_t i = 0; i < linesP.size(); ++i) {
        Vec4i l = linesP[i];
        line(cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
    }

    imshow("Source", src);
    imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
    imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);

    waitKey(0);
    return 0;
}
