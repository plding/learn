#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml.hpp>

#include <vector>
#include <iostream>

#include "DetectRegions.h"
#include "OCR.h"

using namespace cv;
using namespace cv::ml;
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
        input_image = imread(samples::findFile(filename));
    } else {
        cout << "Usage: " << argv[0] << " image" << endl;
        return -1;
    }

    string filename_withoutExt = getFilename(filename);
    cout << "working with file: " << filename_withoutExt << endl;

    // Detect posibles plate regions
    DetectRegions detectRegions;
    detectRegions.setFilename(filename_withoutExt);
    detectRegions.showSteps = false;
    detectRegions.saveRegions = false;
    vector<Plate> posible_regions = detectRegions.run(input_image);

    // SVM for each plate region to get valid car plates
    Ptr<SVM> svm = SVM::load(samples::findFile("SVM.xml"));

    // For each possible plate, classify with svm if it's a plate or no
    vector<Plate> plates;
    for (int i = 0; i < posible_regions.size(); ++i) {
        Mat img = posible_regions[i].plateImg.clone();
        img = img.reshape(1, 1);
        img.convertTo(img, CV_32F);

        if ((int) svm->predict(img) == 1) {
            plates.push_back(posible_regions[i]);
        }
    }

    cout << "Num plates detected: " << plates.size() << endl;
    
    // For each plate detected, recognize it with OCR
    OCR ocr(samples::findFile("OCR.xml"));
    ocr.DEBUG = true;
    ocr.saveSegments = false;
    ocr.filename = filename_withoutExt;
    for (int i = 0; i < plates.size(); ++i) {
        Plate plate = plates[i];

        string plateNumber = ocr.run(&plate);
        string licensePlate = plate.str();
        cout << "============================================\n";
        cout << "License plate number: " << licensePlate << "\n";
        cout << "============================================\n";
        rectangle(input_image, plate.position, Scalar(0, 0, 200));
        putText(input_image, licensePlate, Point(plate.position.x, plate.position.y),
                FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 200), 2);
    }

    imshow("Plate Detected", input_image);

    waitKey();
    return 0;
}
