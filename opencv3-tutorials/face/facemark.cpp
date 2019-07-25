#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/face.hpp>

#include <vector>
#include <iostream>

using namespace cv;
using namespace cv::face;
using namespace std;

int main(int argc, char **argv)
{
    CommandLineParser parser(argc, argv,
            "{image | ../data/lena.jpg | }"
            "{cascade | ../data/lbpcascade_frontalface_improved.xml | }"
            "{model | ../data/lbfmodel.yaml | }"
            "{help h| | }"
            );

    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    Mat src = imread(parser.get<string>("image"));
    if (src.empty()) {
        cerr << "Could not open or find the image!\n" << endl;
        parser.printMessage();
        return -1;
    }
    imshow("Source Image", src);

    CascadeClassifier faceDetector(parser.get<string>("cascade"));
    if (faceDetector.empty()) {
        cerr << "Could not open or find the cascade file!\n" << endl;
        parser.printMessage();
        return -1;
    }

    Ptr<Facemark> facemark = FacemarkLBF::create();
    facemark->loadModel(parser.get<string>("model"));

    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    vector<Rect> faces;
    faceDetector.detectMultiScale(gray, faces);

    if (faces.size() == 0) {
        cout << "Not found face!" << endl;
        return 0;
    }

    vector<vector<Point2f> > landmarks;
    if (facemark->fit(src, faces, landmarks)) {
        for (size_t i = 0; i < landmarks.size(); ++i) {
            drawFacemarks(src, landmarks[i], Scalar(0, 0, 255));
        }
    }

    imshow("Facemarks Result", src);

    waitKey();
    return 0;
}
