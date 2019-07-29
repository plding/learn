#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat img = imread("obama.jpg"); 

    vector<Point2f> points;
    ifstream ifs("obama.txt");
    int x, y;
    while (ifs >> x >> y) {
        points.push_back(Point2f(x, y));
    }

    Rect rect = Rect(0, 0, img.cols, img.rows);
    Subdiv2D subdiv(rect);
    for (vector<Point2f>::const_iterator it = points.begin(); it != points.end(); ++it) {
        subdiv.insert(*it);
    }

    vector<Vec6f> triangleList;
    subdiv.getTriangleList(triangleList);

    for (size_t i = 0; i < triangleList.size(); ++i) {
        Vec6f t = triangleList[i];
        
        vector<Point> pt(3);
        pt[0] = Point(cvRound(t[0]), cvRound(t[1]));
        pt[1] = Point(cvRound(t[2]), cvRound(t[3]));
        pt[2] = Point(cvRound(t[4]), cvRound(t[5]));

        if (rect.contains(pt[0]) && rect.contains(pt[1]) && rect.contains(pt[2])) {
            line(img, pt[0], pt[1], Scalar::all(255), 1, LINE_AA);
            line(img, pt[1], pt[2], Scalar::all(255), 1, LINE_AA);
            line(img, pt[2], pt[0], Scalar::all(255), 1, LINE_AA);
        }
    }

    for (vector<Point2f>::const_iterator it = points.begin(); it != points.end(); ++it) {
        circle(img, *it, 2, Scalar(0, 0, 255), FILLED);
    }

    imshow("Delaunay Triangulation", img);

    waitKey();
    return 0;
}
