#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    CommandLineParser parser(argc, argv,
                             "{@input  |../data/lena.jpg|input image}"
                             "{ksize  k|1|ksize (hit 'K' to increase its value)}"
                             "{scale  s|1|scale (hit 'S' to increase its value)}"
                             "{delta  d|0|delta (hit 'D' to increase its value)}"
                             "{help   h|false|show help message}");

    cout << "The sample uses Sobel or Scharr OpenCV functions for edge detection\n\n";
    parser.printMessage();
    cout << "\nPress 'ESC' to exit program.\nPress 'R' to reset values (ksize will be -1 equal to Scharr function)" << endl;

    Mat image, src, src_gray;
    Mat grad;
    const String window_name = "Sobel Demo - Simple Edge Detector";
    int ksize = parser.get<int>("ksize");
    int scale = parser.get<int>("scale");
    int delta = parser.get<int>("delta");
    int ddepth = CV_16S;

    String imageName = parser.get<String>("@input");
    image = imread(imageName, IMREAD_COLOR);
    if (image.empty()) {
        cout << "Error opening image: " << imageName.c_str() << endl;
        return 1;
    }

    for ( ; ; ) {
        // Remove noise by bluring with a Gaussian filter (kernel size = 3)
        GaussianBlur(image, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

        // Convert the image to grayscale
        cvtColor(src, src_gray, COLOR_BGR2GRAY);

        // Generate grad_x and grad_y
        Mat grad_x, grad_y;
        Mat abs_grad_x, abs_grad_y;

        Sobel(src_gray, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);
        Sobel(src_gray, grad_y, ddepth, 0, 1, ksize, scale, delta, BORDER_DEFAULT);
    
        // converting back to CV_8U
        convertScaleAbs(grad_x, abs_grad_x);
        convertScaleAbs(grad_y, abs_grad_y);

        // Total Gradient (approximate)
        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

        imshow(window_name, grad);
        
        char key = (char) waitKey(0);
        if (key == 27) {
            break;
        } else if (key == 'k' || key == 'K') {
            ksize = ksize < 30 ? ksize + 2 : -1;
        } else if (key == 's' || key == 'S') {
            scale++;
        } else if (key == 'd' || key == 'D') {
            delta++;
        } else if (key == 'r' || key == 'R') {
            scale = 1;
            ksize = -1;
            delta = 0;
        }
    }

    return 0;
}
