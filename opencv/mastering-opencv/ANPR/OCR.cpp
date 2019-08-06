#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "OCR.h"
#include "Plate.h"

using namespace cv;
using namespace std;

OCR::OCR(string trainFile)
{
    DEBUG = false;
    saveSegments = false;
    traind = false;
    charSize = 20;

    FileStorage fs(trainFile, FileStorage::READ);
    Mat TrainingData;
    Mat Classes;
    fs["TrainingDataF15"] >> TrainingData;
    fs["classes"] >> Classes;

    // train(TrainingData, Classes, 10);
}

// void OCR::train(Mat TrainData, Mat classes, int nlayers)
// {
// }

Mat OCR::preprocessChar(Mat in)
{
    int h = in.rows;
    int w = in.cols;
    Mat transformMat = Mat::eye(2, 3, CV_32F);
    int m = max(w, h);
    transformMat.at<float>(0, 2) = m/2 - w/2;
    transformMat.at<float>(1, 2) = m/2 - h/2;

    Mat warpImage(m, m, in.type());
    warpAffine(in, warpImage, transformMat, warpImage.size());

    Mat out;
    resize(warpImage, out, Size(charSize, charSize));

    return out;
}

bool OCR::verifySizes(Mat r)
{
    float aspect = 45.0f / 77.0f;
    float charAspect = (float) r.cols / (float) r.rows;
    float error = 0.35;
    float minHeight = 15;
    float maxHeight = 28;
    float minAspect = 0.2;
    float maxAspect = aspect + aspect * error;
    float area = countNonZero(r);
    float bbArea = r.cols * r.rows;
    float percPixels = area / bbArea;
    if (percPixels < 0.8 && charAspect > minAspect && charAspect < maxAspect && r.rows >= minHeight && r.rows < maxHeight)
        return true;
    else 
        return false;
}

vector<CharSegment> OCR::segment(Plate plate)
{
    Mat input = plate.plateImg;
    vector<CharSegment> output;

    // Threshold input image
    Mat img_threshold;
    threshold(input, img_threshold, 60, 255, CV_THRESH_BINARY_INV);
    if (DEBUG) {
        imshow("Threshold plate", img_threshold);
    }

    // Find contours of possibles characters
    vector<vector<Point> > contours;
    findContours(img_threshold, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Draw blue contours on a white image
    Mat result = input.clone();
    drawContours(result, contours, -1, Scalar(255, 0, 0), 1);

    // Start to iterate to each contour founded
    vector<vector<Point> >::iterator itc = contours.begin();
    while (itc != contours.end()) {
        Rect mr = boundingRect(*itc);
        // Crop image
        Mat auxRoi(img_threshold, mr);
        if (verifySizes(auxRoi)) {
            output.push_back(CharSegment(auxRoi, mr));
            rectangle(result, mr, Scalar(0, 125, 255));
        }
        ++itc;
    }
    if (DEBUG) {
        cout << "Num chars: " << output.size() << endl;
        imshow("SEgmented Chars", result);
    }

    return output;
}

Mat OCR::ProjectedHistogram(Mat img, int t)
{
    int sz = t ? img.rows : img.cols;
    Mat mhist = Mat::zeros(1, sz, CV_32F);

    for (int j = 0; j < sz; ++j) {
        Mat data = t ? img.row(j) : img.col(j);
        mhist.at<float>(j) = countNonZero(data);
    }

    // Normalized histogram
    double min, max;
    minMaxLoc(mhist, &min, &max);

    if (max > 0) {
        mhist.convertTo(mhist, -1, 1.0f/max, 0);
    }

    return mhist;
}

void OCR::drawVisualFeatures(Mat character, Mat hhist, Mat vhist, Mat lowData)
{
    Mat img(121, 121, CV_8UC3, Scalar(0, 0, 0));
    Mat ch;
    Mat ld;

    cvtColor(character, ch, COLOR_GRAY2BGR);
}

Mat OCR::features(Mat in, int sizeData)
{
    Mat vhist = ProjectedHistogram(in, VERTICAL); 
    Mat hhist = ProjectedHistogram(in, HORIZONTAL); 

    Mat lowData;
    resize(in, lowData, Size(sizeData, sizeData));

    if (DEBUG) {
        drawVisualFeatures(in, hhist, vhist, lowData);
    }

    int numCols = vhist.cols + hhist.cols + lowData.cols * lowData.cols;
    Mat out = Mat::zeros(1, numCols, CV_32F);

    // Asign values to feature
    int j = 0;
    for (int i = 0; i < vhist.cols; ++i) {
        out.at<float>(j++) = vhist.at<float>(i);
    }
    for (int i = 0; i < hhist.cols; ++i) {
        out.at<float>(j++) = hhist.at<float>(i);
    }
    for (int x = 0; x < lowData.cols; ++x) {
        for (int y = 0; y < lowData.rows; ++y) {
            out.at<float>(j++) = (float) lowData.at<unsigned char>(x, y);
        }
    }
    if (DEBUG) {
        cout << out << "\n=================================================\n";
    }

    return out;
}

// int OCR::classify(Mat f)
// {
//     Mat output(1, numCharacters, CV_32F);
//     ann.predict(f, output);
//     Point maxLoc;
//     double maxVal;
//     minMaxLoc(output, 0, &maxVal, &maxLoc);
// 
//     return maxLoc.x;
// }

string OCR::run(Plate *input)
{
    vector<CharSegment> segments = segment(*input);

    for (int i = 0; i < segments.size(); ++i) {
        Mat ch = preprocessChar(segments[i].img);
        if (saveSegments) {
            ostringstream ss;
            ss << "tmpChars/" << filename << "_" << i << ".jpg";
            imwrite(ss.str(), ch);
        }
        // For each segment Extract Features
        Mat f = features(ch, 15);
        // For each segment feature Classify
        // int character = classify(f);
    }

    return input->str();
}
