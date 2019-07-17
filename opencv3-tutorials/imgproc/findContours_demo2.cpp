#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

Mat src_gray;
RNG rng(12345);
void thresh_callback(int value, void *data);

int main(int argc, char **argv)
{
    CommandLineParser parser(argc, argv, "{@input | ../data/HappyFish.jpg | input image}");
    Mat src = imread(parser.get<String>("@input"));
    if (src.empty()) {
        cout << "Could not open or find the image!\n" << endl;
        parser.printMessage();
        return -1;
    }

    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));

    const char *window_name = "Source";
    namedWindow(window_name);
    imshow(window_name, src);

    int thresh = 100;
    createTrackbar("Canny Thresh:", window_name, &thresh, 255, thresh_callback);
    thresh_callback(thresh, NULL);
    
    waitKey();
    return 0;
}

void thresh_callback(int value, void *data)
{
    Mat edges;
    Canny(src_gray, edges, value, value * 2);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    cout << contours.size() << endl;

    Mat drawing = Mat::zeros(src_gray.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); ++i) {
        Scalar color(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours, (int) i, color, 2, 8, hierarchy, 0);
    }

    imshow("Contours", drawing);
}
