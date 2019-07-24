#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <string>
#include <iostream>

using namespace cv;
using namespace std;

int maskSize0 = DIST_MASK_5;
int voronoiType = -1;
int edgeThresh = 100;
int distType0 = DIST_L1;

Mat gray;

static void onTrackbar(int, void *)
{
    static const Scalar colors[] = {
        Scalar(0, 0, 0),
        Scalar(255, 0, 0),
        Scalar(255, 128, 0),
        Scalar(255, 255, 0),
        Scalar(0, 255, 0),
        Scalar(0, 128, 255),
        Scalar(0, 255, 255),
        Scalar(0, 0, 255),
        Scalar(255, 0, 255)
    };

    int maskSize = voronoiType >= 0 ? DIST_MASK_5 : maskSize0;
    int distType = voronoiType >= 0 ? DIST_L1 : distType0;

    Mat edge = gray >= edgeThresh, dist, labels, dist8u;

    if (voronoiType < 0) {
        distanceTransform(edge, dist, distType, maskSize);
    } else {
        distanceTransform(edge, dist, labels, distType, maskSize, voronoiType);
    }

    if (voronoiType < 0) {
        dist *= 5000;
        pow(dist, 0.5, dist);

        Mat dist32s, dist8u1, dist8u2;

        dist.convertTo(dist32s, CV_32S, 1, 0.5);
        dist32s &= Scalar::all(255);

        dist32s.convertTo(dist8u1, CV_8U, 1, 0);
        dist32s *= -1;

        dist32s += Scalar::all(255);
        dist32s.convertTo(dist8u2, CV_8U);

        Mat planes[] = {dist8u1, dist8u2, dist8u2};
        merge(planes, 3, dist8u);
    }

    imshow("Distance Map", dist8u);
}

static void help()
{
    cout << "Program to demonstrate the use of the distance transform function between edge images.\n"
         << "Usage:\n"
         << "./distrans [image_name -- default image is stuff.jpg]\n"
         << "\nHot keys: \n"
         << "\tESC - quit the program\n"
         << "\tC - use C/Inf metric\n"
         << "\tL1 - use L1 metric\n"
         << "\tL2 - use L2 metric\n"
         << "\t3 - use 3x3 mask\n"
         << "\t5 - use 5x5 mask\n"
         << "\t0 - use precise distance transform\n"
         << "\tv - switch to Voronoi diagram mode\n"
         << "\tp - switch to pixel-based Voronoi diagram mode\n"
         << "\tSPACE - loop through all the modes\n\n";
}

int main(int argc, char **argv)
{
    CommandLineParser parser(argc, argv, "{help h||}{@image | stuff.jpg | input image file}");
    if (parser.has("help")) {
        help();
        return 0;
    }

    string filename = parser.get<string>(0);
    gray = imread(samples::findFile(filename), 0);
    if (gray.empty()) {
        cout << "Cannot read image file: " << filename.c_str() << endl;
        help();
        return -1;
    }

    namedWindow("Distance Map");
    createTrackbar("Brightness Threshold", "Distance Map", &edgeThresh, 255, onTrackbar, 0);

    for ( ; ; ) {
        onTrackbar(0, 0);

        char c = (char) waitKey();

        if (c == 27)
            break;
    }

    return 0;
}
