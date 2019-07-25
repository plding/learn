#ifndef OCR_H
#define OCR_H

#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include <string>
#include "Plate.h"

#define NUM_CHARACTERS = 30;

#define VERTICAL   0
#define HORIZONTAL 1

class CharSegment
{
public:
    cv::Mat img;
    cv::Rect pos;
    CharSegment(cv::Mat i, cv::Rect p) : img(i), pos(p) {};
};

class OCR
{
public:
    bool DEBUG;
    bool saveSegments;
    bool traind;
    int charSize;
    std::string filename;

    OCR(std::string trainFile);
    std::string run(Plate *input);
    cv::Mat features(cv::Mat in, int size);

private:
    cv::Ptr<cv::ml::ANN_MLP> ann;

    std::vector<CharSegment> segment(Plate input);
    bool verifySizes(cv::Mat in);
    cv::Mat preprocessChar(cv::Mat in);
    cv::Mat ProjectedHistogram(cv::Mat in, int t);
    void drawVisualFeatures(cv::Mat in, cv::Mat hhist, cv::Mat vhist, cv::Mat lowData);
};

#endif /* OCR_H */
