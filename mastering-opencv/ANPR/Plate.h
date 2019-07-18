#ifndef PLATE_H
#define PLATE_H

#include <opencv2/core.hpp>
#include <vector>

class Plate
{

public:
    cv::Mat plateImg;
    cv::Rect position;

    Plate();
    Plate(cv::Mat img, cv::Rect pos) : plateImg(img), position(pos) {};
};

#endif /* PLATE_H */
