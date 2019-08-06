#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

const char *keys =
    "{help h||}"
    "{image | ../data/image.jpg | Path to image. }"
    "{face_cascade | ../data/haarcascade_frontalface_alt.xml | Path to face cascade. }"
    "{eyes_cascade | ../data/haarcascade_eye_tree_eyeglasses.xml | Path to eye cascade. }";

void detectAndDisplay(Mat image);

// Global variables
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

int main(int argc, char **argv)
{
    CommandLineParser parser(argc, argv, keys);

    Mat image = imread(parser.get<String>("image"));
    if (image.empty()) {
        cout << "Could not open or find the image!\n" << endl;
        parser.printMessage();
        return -1;
    }

    //-- 1. Load the cascades
    if (!face_cascade.load(parser.get<String>("face_cascade"))) {
        cout << "--(!)Error loading face cascade\n" << endl;
        parser.printMessage();
        return -1;
    }
    if (!eyes_cascade.load(parser.get<String>("eyes_cascade"))) {
        cout << "--(!)Error loading eyes cascade\n" << endl;
        parser.printMessage();
        return -1;
    }

    //-- 2. Apply the classifier
    detectAndDisplay(image);

    waitKey();
    return 0;
}

void detectAndDisplay(Mat image)
{
    Mat image_gray;
    cvtColor(image, image_gray, COLOR_BGR2GRAY);
    equalizeHist(image_gray, image_gray);

    //-- Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(image_gray, faces, 1.1, 3, 0, image.size() / 10);

    for (size_t i = 0; i < faces.size(); ++i) {
        Point center(faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2);
        ellipse(image, center, Size(faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar(0, 0, 255), 2);

        Mat faceROI = image_gray(faces[i]);

        //-- In each face, detect eyes
        std::vector<Rect> eyes;
        eyes_cascade.detectMultiScale(faceROI, eyes);

        for (size_t j = 0; j < eyes.size(); ++j) {
            Point eye_center(faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2);
            circle(image, eye_center, cvRound((eyes[j].width + eyes[j].height) * 0.25), Scalar(255, 0, 0), 2);
        }
    }

    //-- Show what you got
    imshow("Capture - Face detection", image);
}
