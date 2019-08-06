#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

const char *window_name = "Pyramids Demo";

int main(int argc, char **argv)
{
    cout << "\n Zoom In-Out demo \n"
         << "------------------- \n"
         << " * [i] -> Zoom in   \n"
         << " * [o] -> Zoom out  \n"
         << " * [ESC] -> Close program \n" << endl;

    const char *filename = argc >= 2 ? argv[1] : "../data/chicky_512.png";

    // Loads an image
    Mat src = imread(filename);
    if (src.empty()) {
        cout << "Error opening image" << endl;
        cout << "Program Arguments: [image_name -- default ../data/chicky_512.png]" << endl;
        return -1;
    }

    for ( ; ; ) {
        imshow(window_name, src);
        
        char c = (char) waitKey(0);
        if (c == 27) {
            break;
        } else if (c == 'i') {
            pyrUp(src, src, Size(src.cols * 2, src.rows * 2));
            cout << "** Zoom In: Image x 2" << endl;
        } else if (c == 'o') {
            pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
            cout << "** Zoom Out: Image / 2" << endl;
        }
    }

    return 0;
}
