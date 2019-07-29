#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    // Read image
    Mat im = imread("blob.jpg", IMREAD_GRAYSCALE);

    // Setup SimpleBlobDetector parameters
    SimpleBlobDetector::Params params;

    // Change thresholds
    params.minThreshold = 10;
    params.maxThreshold = 200;

    // Filter by Area
    params.filterByArea = true;
    params.minArea = 1500;

    // Filter by Circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.1;

    // Filter by Convexity
    params.filterByConvexity = true;
    params.minConvexity = 0.87;

    // Filter by Intertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.01;

    // Storage for blobs
    vector<KeyPoint> keypoints;

    // Set up detector with params
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

    // Detect blobs
    detector->detect(im, keypoints);

    // Draw detected blobs as red circles
    // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures
    // the size of the circle corresponds to the size of blob
    Mat im_with_keypoints;
    drawKeypoints(im, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    // Show blobs
    imshow("keypoints", im_with_keypoints);
    waitKey();

    return 0;
}
