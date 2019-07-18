#ifndef DETECTREGIONS_H
#define DETECTREGIONS_H

#include <opencv2/core.hpp>
#include <string>
#include <vector>

#include "Plate.h"

class DetectRegions
{

public:
    std::string filename;
    bool showSteps;
    bool saveRegions;

    DetectRegions() : showSteps(false), saveRegions(false) {};
    void setFilename(std::string f) { filename = f; };
    std::vector<Plate> run(cv::Mat input);

private:
    std::vector<Plate> segment(cv::Mat input);
    bool verifySizes(cv::RotatedRect mr);
    cv::Mat histeq(cv::Mat in);
};

#endif /* DETECTREGIONS_H */
