#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <vector>
#include <iostream>

#include "DetectRegions.h"

using namespace cv;
using namespace std;

string getFilename(string s)
{
    char sep = '/';
    char sepExt = '.';

    size_t i = s.rfind(sep, s.length());
    if (i != string::npos) {
        string fn = s.substr(i + 1, s.length() - i);
        size_t j = fn.rfind(sepExt, fn.length());
        if (i != string::npos) {
            return fn.substr(0, j);
        } else {
            return fn;
        }
    } else {
        return "";
    }
}

int main(int argc, char **argv)
{
    cout << "OpenCV Automatic Number Plate Recognition" << endl;
    
    char *filename;
    Mat input_image;
    if (argc >= 2) {
        filename = argv[1];
        input_image = imread(filename);
    } else {
        cout << "Usage: " << argv[0] << " image" << endl;
        return -1;
    }

    string filename_withoutExt = getFilename(filename);
    cout << "working with file: " << filename_withoutExt << endl;

    // Detect posibles plate regions
    DetectRegions detectRegions;
    detectRegions.setFilename(filename_withoutExt);
    detectRegions.showSteps = true;
    detectRegions.saveRegions = true;
    detectRegions.run(input_image);

    waitKey();
    return 0;
}
