#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

void update_map(int &ind, Mat &map_x, Mat &mat_y);

int main(int argc, char **argv)
{
    CommandLineParser parser(argc, argv, "{@image|../data/chicky_512.png|input image name}");
    string filename = parser.get<string>(0);
    
    // Load the image
    Mat src = imread(filename, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot read image: " << filename << endl;
        return -1;
    }

    // Create dst, map_x and map_y with the same size as src
    Mat dst(src.size(), src.type());
    Mat map_x(src.size(), CV_32FC1);
    Mat map_y(src.size(), CV_32FC1);

    // Create window
    const char *remap_window = "Remap demo";
    namedWindow(remap_window, WINDOW_AUTOSIZE);

    int ind = 0;
    for ( ; ; ) {
        // Update map_x & map_y. Then apply remap
        update_map(ind, map_x, map_y);
        remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

        // Display results
        imshow(remap_window, dst);

        // Each 1 sec. Press ESC to exit the program
        char c = (char) waitKey(1000);
        if (c == 27) {
            break;
        }
    }

    return 0;
}

void update_map(int &ind, Mat &map_x, Mat &map_y)
{
    for (int i = 0; i < map_x.rows; ++i) {
        for (int j = 0; j < map_x.cols; ++j) {
            switch (ind) {
                
            case 0:
                if (j > map_x.cols * 0.25 && j < map_x.cols * 0.75 &&
                    i > map_x.rows * 0.25 && i < map_x.rows * 0.75) {
                    map_x.at<float>(i, j) = 2 * (j - map_x.cols * 0.25f) + 0.5f;
                    map_y.at<float>(i, j) = 2 * (i - map_x.rows * 0.25f) + 0.5f;
                } else {
                    map_x.at<float>(i, j) = 0; 
                    map_y.at<float>(i, j) = 0; 
                }
                break;

            case 1:
                map_x.at<float>(i, j) = (float) j;
                map_y.at<float>(i, j) = (float) (map_x.rows - i);
                break;

            case 2:
                map_x.at<float>(i, j) = (float) (map_x.cols - j);
                map_y.at<float>(i, j) = (float) i;
                break;

            case 3:
                map_x.at<float>(i, j) = (float) (map_x.cols - j);
                map_y.at<float>(i, j) = (float) (map_x.rows - i);
                break;
            }
        }
    }

    ind = (ind + 1) % 4;
}
