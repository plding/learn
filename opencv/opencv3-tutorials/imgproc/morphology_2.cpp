#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat src, dst;

int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;

const char *window_name = "Morphology Transformations Demo";

void Morphology_Operations(int, void *);

int main(int argc, char **argv)
{
    CommandLineParser parser(argc, argv, "{@input | ../data/baboon.jpg | input image}");
    src = imread(parser.get<String>("@input"), IMREAD_COLOR);
    if (src.empty()) {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    namedWindow(window_name, WINDOW_AUTOSIZE);

    createTrackbar("Operator:", window_name, &morph_operator, max_operator, Morphology_Operations);
    createTrackbar("Element:", window_name, &morph_elem, max_elem, Morphology_Operations);
    createTrackbar("Kernel Size:", window_name, &morph_size, max_kernel_size, Morphology_Operations);

    Morphology_Operations(0 ,0);

    waitKey(0);
    return 0;
}

void Morphology_Operations(int, void *)
{
    int operation = morph_operator + 2;

    Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1),
                    Point(morph_size, morph_size));

    morphologyEx(src, dst, operation, element);
    imshow(window_name, dst);
}
