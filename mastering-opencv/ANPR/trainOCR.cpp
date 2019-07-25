#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>

#include <string>
#include <vector>
#include <iostream>

#include "OCR.h"

using namespace cv;
using namespace cv::ml;
using namespace std;

int main(int argc, char **argv)
{
    cout << "OpenCV Training OCR Automatic Number Plate Recognition" << endl << endl;

    char *path;
    if (argc == 2) {
        path = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " <path to chars folders files>" << endl;
        return 0;
    }

    Ptr<ANN_MLP> ann = ANN_MLP::create();
    ann->setLayerSizes(Mat_<int>(1, 3) << 1, 10, NUM_CHARACTERS);
    // ann->setTrainMethod(ANN_MLP::BACKPROP, 0.1, 0.1);
    // ann->setActivationFunction(ANN_MLP::SIGMOID_SYM);
    ann->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 1000, 1e-6));
    ann->train(data, ROW_SAMPLE, labels);
    ann->save("OCR.xml");

    return 0;
}
