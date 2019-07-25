#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace cv::face;
using namespace std;

static Mat norm_0_255(InputArray _src)
{
    Mat dst;

    switch (_src.channels()) {
    case 1:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        _src.getMat().copyTo(dst);
        break;
    }

    return dst;
}

static void read_csv(const string &filename, vector<Mat> &images, vector<int> &labels, char separator = ';')
{
    ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        CV_Error(Error::StsBadArg, "No valid input file was given, please check the given filename.");
    }

    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if (!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

int main(int argc, const char **argv)
{
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <csv.ext> <output_folder>" << endl;
        exit(1);
    }

    string fn_csv = string(argv[1]);
    string output_folder = ".";
    if (argc == 3) {
        output_folder = string(argv[2]);
    }

    // These vectors hold the images and corresponding labels.
    vector<Mat> images;
    vector<int> labels;

    // Read in the data. This can fail if no valid input filename is given.
    try {
        read_csv(fn_csv, images, labels);
    } catch (const cv::Exception &e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        exit(1);
    }

    // Quit if there are not enough images for this demo
    if (images.size() <= 1) {
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        CV_Error(Error::StsError, error_message);
    }

    Mat testSample = images[images.size() - 1];
    int testLabel  = labels[labels.size() - 1];
    images.pop_back();
    labels.pop_back();

    // Create an Eigenfaces model for face recognition and train it with the images and
    // labels read from the given CSV file.
    // This here is a full PCA, if you just want to keep 10 principal components, then
    // call the factory method like this:
    //
    //      EigenFaceRecognizer::create(10);
    //
    // If you want to create a FaceRecognizer with a confidence threshold, call it with:
    //
    //      EigenFaceRecognizer::create(10, 123.0);
    //
    Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create();
    model->train(images, labels);

    // To get the confidence of a prediction call the model with:
    //
    //      int predictedLabel = -1;
    //      double confidence  = 0.0;
    //      model->predict(testSample, predictedLabel, confidence);
    //
    int predictedLabel = model->predict(testSample);
    cout << "Predicted class = " << predictedLabel << " / Actual class = " << testLabel << "." << endl;

    // Here is how to get the eigenvalues of this Eigenfaces model:
    Mat eigenvalues = model->getEigenValues();
    // And we can do the same to display the Eigenvectors:
    Mat W = model->getEigenVectors();
    // Get the sample mean from the training data
    Mat mean = model->getMean();
    // Display or save:
    if (argc == 2) {
        imshow("mean", norm_0_255(mean.reshape(1, images[0].rows)));
    } else {
        imwrite(format("%s/mean.png", output_folder.c_str()), norm_0_255(mean.reshape(1, images[0].rows)));
    }
    // Display or save the Eigenfaces:
    for (int i = 0; i < min(10, W.cols); ++i) {
        cout << format("Eigenvalue #%d = %.5f", i, eigenvalues.at<double>(i)) << endl;
        // get eigenvector #i
        Mat ev = W.col(i).clone();
        // Reshape to original size & normalize to [0...255] for imshow.
        Mat grayscale = norm_0_255(ev.reshape(1, images[0].rows));
        // Show the image & apply a Jet colormap for better sensing.
        Mat cgrayscale;
        applyColorMap(grayscale, cgrayscale, COLORMAP_JET);
        // Display or save:
        if (argc == 2) {
            imshow(format("eigenface_%d", i), grayscale);
        } else {
            imwrite(format("%s/eigenface_%d.png", output_folder.c_str(), i), grayscale);
        }
    }

    if (argc == 2) {
        waitKey();
    }

    return 0;
}
