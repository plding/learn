#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

struct userdata {
    Mat im;
    vector<Point2f> points;
};

void mouseHandler(int event, int x, int y, int flags, void *data_ptr)
{
    if (event == EVENT_LBUTTONDOWN) {
        userdata *data = (userdata *) data_ptr;
        circle(data->im, Point(x, y), 3, Scalar(0, 255, 255), 5, LINE_AA);
        imshow("Image", data->im);
        if (data->points.size() < 4) {
            data->points.push_back(Point2f(x, y));
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <source image path> <destination image path>" << endl;
        return 1;
    }

    // Read in the image
    Mat im_src = imread(argv[1]);
    Mat im_dst = imread(argv[2]);

    // Create a vector of points
    vector<Point2f> pts_src;
    pts_src.push_back(Point2f(0, 0));
    pts_src.push_back(Point2f(im_src.cols - 1, 0));
    pts_src.push_back(Point2f(im_src.cols - 1, im_src.rows - 1));
    pts_src.push_back(Point2f(0, im_src.rows - 1));

    namedWindow("Image");

    userdata data;
    data.im = im_dst.clone();

    // Set the callback function for any mouse event
    setMouseCallback("Image", mouseHandler, &data);

    // Show the image
    imshow("Image", data.im);
    waitKey();

    Mat tform = findHomography(pts_src, data.points);
    warpPerspective(im_src, data.im, tform, data.im.size());

    Point pts_dst[4];
    for (int i = 0; i < 4; ++i) {
        pts_dst[i] = data.points[i];
    }

    fillConvexPoly(im_dst, pts_dst, 4, Scalar(0), LINE_AA);

    im_dst = im_dst + data.im;

    imshow("Image", im_dst);
    waitKey();

    return 0;
}
