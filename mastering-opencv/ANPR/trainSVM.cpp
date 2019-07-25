#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml.hpp>

#include <vector>
#include <iostream>

#define OPENCV_SAMPLES_DATA_PATH /Users/edz/learn/mastering-opencv/ANPR

using namespace cv;
using namespace cv::ml;
using namespace std;

int main(int argc, char **argv)
{
    cout << "OpenCV Training SVM Automatic Number Plate Recognition" << endl << endl;

    char *pathPlates;
    char *pathNoPlates;
    int numPlates;
    int numNoPlates;

    if (argc >= 5) {
        numPlates    = atoi(argv[1]);
        numNoPlates  = atoi(argv[2]); 
        pathPlates   = argv[3];
        pathNoPlates = argv[4];
    } else {
        cout << "Usage: " << argv[0] << " <num plate> <num non-plate> <path to plate> <path to non-plate>\n";
        return 0;
    }

    Mat trainingImages;
    vector<int> trainingLabels;

    for (int i = 0; i < numPlates; ++i) {
        ostringstream ss;
        ss << pathPlates << i << ".jpg";
        Mat img = imread(ss.str(), IMREAD_GRAYSCALE);
        img = img.reshape(1, 1);
        trainingImages.push_back(img);
        trainingLabels.push_back(1);
    }

    for (int i = 0; i < numNoPlates; ++i) {
        ostringstream ss;
        ss << pathNoPlates << i << ".jpg";
        Mat img = imread(ss.str(), IMREAD_GRAYSCALE);
        img = img.reshape(1, 1);
        trainingImages.push_back(img);
        trainingLabels.push_back(0);
    }

    trainingImages.convertTo(trainingImages, CV_32F);

    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setC(1);
    svm->setKernel(SVM::LINEAR);
    svm->train(trainingImages, ROW_SAMPLE, trainingLabels);
    svm->save(samples::findFile("SVM.xml"));

    return 0;
}
