#ifndef PLATE_H
#define PLATE_H

#include <opencv2/core.hpp>
#include <vector>
#include <string>

class Plate
{
public:
    cv::Mat plateImg;
    cv::Rect position;
    std::vector<char> chars;
    std::vector<cv::Rect> charsPos;

    Plate(cv::Mat img, cv::Rect pos) : plateImg(img), position(pos) {};
    std::string str();
};

#endif /* PLATE_H */
