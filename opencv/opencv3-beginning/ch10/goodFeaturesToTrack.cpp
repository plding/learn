#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

#include <vector>
using namespace std;

int main()
{
    Mat image = imread("../images/church.jpg", 0);
    imshow("Original Image", image);

    vector<Point2f> corners;
    goodFeaturesToTrack(image, corners, 500, 0.01, 10);

    for (auto it = corners.begin(); it != corners.end(); ++it)
        circle(image, *it, 3, Scalar(255), 1);
    imshow("Circle Image", image);

    waitKey();
    return 0;
}
