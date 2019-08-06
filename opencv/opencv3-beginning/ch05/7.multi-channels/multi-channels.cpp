#include <opencv2/opencv.hpp>
using namespace cv;

#include <iostream>
#include <string>
using namespace std;

int main(int argc, const char **argv)
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " {red|green|blue}" << endl;
        return -1;
    }

    String color(argv[1]);

    int pos;
    if (color == "blue") {
        pos = 0;
    } else if (color == "green") {
        pos = 1;
    } else if (color == "red") {
        pos = 2;
    } else {
        cerr << "Error color value!" << endl;
        return -1;
    }

    Mat image = imread("dota_jugg.jpg");
    Mat logo  = imread("dota_logo.jpg", 0);

    vector<Mat> channels;
    split(image, channels);

    Mat channel = channels.at(pos);
    Mat roi = channel(Rect(500, 250, logo.cols, logo.rows));
    addWeighted(roi, 1.0, logo, 0.5, 0.0, roi);

    merge(channels, image);
    imshow((color + " channel result").c_str(), image);
    waitKey(0);

    return 0;
}
