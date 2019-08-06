#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/face.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace cv;
using namespace cv::face;
using namespace std;

static bool myDetector(InputArray image, OutputArray faces, CascadeClassifier *face_cascade)
{
    Mat gray;

    if (image.channels() > 1)
        cvtColor(image, gray, COLOR_BGR2GRAY);
    else
        gray = image.getMat().clone();

    equalizeHist(gray, gray);

    vector<Rect> faces_;
    face_cascade->detectMultiScale(gray, faces_, 1.4, 2, CASCADE_SCALE_IMAGE, Size(30, 30));
    Mat(faces_).copyTo(faces);
    return true;
}

int main(int argc, char **argv)
{
    CommandLineParser parser(argc, argv,
        "{ help h usage ?    |      | give the following arguments in following format }"
        "{ model_filename f  |      | (required) path to binary file storing the trained model which is to be loaded [example - /data/file.dat]}"
        "{ image i           |      | (required) path to image in which face landmarks have to be detected.[example - /data/image.jpg] }"
        "{ face_cascade c    |      | Path to the face cascade xml file which you want to use as a detector}"
    );

    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }
    string filename(parser.get<string>("model_filename"));
    if (filename.empty()) {
        cerr << "The name  of  the model file to be loaded for detecting landmarks is not found" << endl;
        parser.printMessage();
        return -1;
    }
    string image(parser.get<string>("image"));
    if (image.empty()) {
        cerr << "The name  of  the image file in which landmarks have to be detected is not found" << endl;
        parser.printMessage();
        return -1;
    }
    string cascade_name(parser.get<string>("face_cascade"));
    if (cascade_name.empty()) {
        cerr << "The name of the cascade classifier to be loaded to detect faces is not found" << endl;
        parser.printMessage();
        return -1;
    }

    Mat img = imread(image);
    resize(img, img, Size(460, 460), 0, 0, INTER_LINEAR_EXACT);

    CascadeClassifier face_cascade(cascade_name);

    Ptr<FacemarkTrain> facemark = FacemarkLBF::create();
    facemark->setFaceDetector((FN_FaceDetector) myDetector, &face_cascade);
    facemark->loadModel(filename);

    vector<Rect> faces;
    facemark->getFaces(img, faces);

    if (faces.size() != 0) {
        vector<vector<Point2f> > shapes;
        if (facemark->fit(img, faces, shapes)) {
            for (size_t i = 0; i < faces.size(); ++i) {
                rectangle(img, faces[i], Scalar(255, 0, 0));
                for (size_t j = 0; j < shapes[i].size(); ++j) {
                    circle(img, shapes[i][j], 2, Scalar(0, 0, 255), FILLED);
                }
            }
            imshow("Detected_shape", img);
            waitKey(0);
        }
    } else {
        cout << "Faces not detected." << endl;
    }

    return 0;
}
