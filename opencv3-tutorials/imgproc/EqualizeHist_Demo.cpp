#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    // Load image
    CommandLineParser parser(argc, argv, "{@input | ../data/lena.jpg | input image}");
    Mat src = imread(parser.get<String>("@input"), IMREAD_COLOR);
    if (src.empty()) {
        cout << "Could not open or find the image!\n" << endl;
        parser.printMessage();
        return -1;
    }

    // Convert to grayscale
    cvtColor(src, src, COLOR_BGR2GRAY);

    // Apply Histogram Equalization
    Mat dst;
    equalizeHist(src, dst);

    // Display results
    imshow("Source Image", src);
    imshow("Equalized Image", dst);

    waitKey();
    return 0;
}
