#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>

using namespace cv;
using namespace cv::ml;

int main(int argc, char **argv)
{
    // Set up training data
    int labels[4] = { 1, -1, -1, -1 };
    float trainingData[4][2] = { {501, 10}, {255, 10}, {501, 255}, {10, 501} };
    Mat trainingDataMat(4, 2, CV_32F, trainingData); 
    Mat labelsMat(4, 1, CV_32SC1, labels);

    // Train the SVM
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
    svm->train(trainingDataMat, ROW_SAMPLE, labelsMat);
    // svm->save("svm_test.xml");
    // Ptr<SVM> svm = SVM::load("svm_test.xml");

    // Data for visual representation
    int width = 512, height = 512;
    Mat image = Mat::zeros(height, width, CV_8UC3);

    // Show the decision regions given by the SVM
    Vec3b green(0, 255, 0), blue(255, 0, 0);
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            Mat sampleMat = (Mat_<float>(1, 2) << j, i);
            float response = svm->predict(sampleMat);

            if (response == 1)
                image.at<Vec3b>(i, j) = green;
            else if (response == -1)
                image.at<Vec3b>(i, j) = blue;
        }
    }

    // Show the training data
    for (int i = 0; i < 4; ++i) {
        Scalar color;
        if (labels[i] == 1) {
            color = Scalar(0, 0, 0); 
        } else {
            color = Scalar(255, 255, 255);
        }

        circle(image, Point(trainingData[i][0], trainingData[i][1]), 5, color, -1);
    }

    // Show support vectors
    Mat sv = svm->getUncompressedSupportVectors();
    for (int i = 0; i < sv.rows; ++i) {
        const float *v = sv.ptr<float>(i);
        circle(image, Point((int) v[0], (int) v[1]), 6, Scalar(128, 128, 128), 2);
    }

    imshow("SVM Simple Example", image);
    waitKey();
    return 0;
}
