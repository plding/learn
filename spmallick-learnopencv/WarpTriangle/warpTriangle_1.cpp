#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void warpTriangle(Mat &img1, Mat &img2, vector<Point> tri1, vector<Point> tri2)
{
    Rect r1 = boundingRect(tri1);
    Rect r2 = boundingRect(tri2);

    vector<Point2f> tri1Cropped, tri2Cropped;
    vector<Point> tri2CroppedInt;
    for (int i = 0; i < 3; ++i) {
        tri1Cropped.push_back(Point2f(tri1[i].x - r1.x, tri1[i].y - r1.y));
        tri2Cropped.push_back(Point2f(tri2[i].x - r2.x, tri2[i].y - r2.y));

        tri2CroppedInt.push_back(Point(tri2[i].x - r2.x, tri2[i].y - r2.y));
    }

    Mat warpMat = getAffineTransform(tri1Cropped, tri2Cropped);

    Mat img2Warpped;
    warpAffine(img1(r1), img2Warpped, warpMat, r2.size(), INTER_LINEAR, BORDER_REFLECT_101); 

    Mat mask = Mat::zeros(r2.size(), img2.type());
    fillConvexPoly(mask, tri2CroppedInt, Scalar::all(255), LINE_AA);

    img2(r2) = ~mask + (img2Warpped & mask);
}

int main()
{
    Mat src = imread("robot.jpg");
    Mat dst = Mat(src.size(), src.type(), Scalar::all(255));

    vector<Point> tri1;
    tri1.push_back(Point(360, 200));
    tri1.push_back(Point( 60, 250));
    tri1.push_back(Point(450, 400));

    vector<Point> tri2;
    tri2.push_back(Point(400, 200));
    tri2.push_back(Point(160, 270));
    tri2.push_back(Point(400, 400));

    warpTriangle(src, dst, tri1, tri2);

    polylines(src, tri1, true, Scalar(255, 150, 0), 2, LINE_AA);
    polylines(dst, tri2, true, Scalar(255, 150, 0), 2, LINE_AA);

    imshow("Input", src);
    imshow("Output", dst);
    waitKey();

    return 0;
}
