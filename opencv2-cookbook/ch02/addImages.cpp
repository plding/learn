#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

int main()
{
    cv::Mat image1;
    cv::Mat image2;

    image1 = cv::imread("../images/boldt.jpg");
    image2 = cv::imread("../images/rain.jpg");
    if (!image1.data || !image2.data)
        return -1;

    cv::imshow("Image 1", image1);
    cv::imshow("Image 2", image2);

    cv::Mat result;
    cv::addWeighted(image1, 0.7, image2, 0.9, 0.0, result);
    cv::imshow("result", result);

    // using overloaded operator
    result = 0.7 * image1 + 0.9 * image2;
    cv::imshow("result with operators", result);

    image2 = cv::imread("../images/rain.jpg", 0);

    // create vector of 3 images
    std::vector<cv::Mat> planes;
    // split 1 3-channel image into 3 1-channel images
    cv::split(image1, planes);
    // add to blue channel
    planes[0] += image2;
    // merge the 3 1-channel images into 1 3-channel image
    cv::merge(planes, result);
    cv::imshow("Result on blue channel", result);

    // read images
    cv::Mat image = cv::imread("../images/boldt.jpg");
    cv::Mat logo  = cv::imread("../images/logo.bmp");

    // define image ROI
    cv::Mat imageROI = image(cv::Rect(385, 270, logo.cols, logo.rows));

    // add logo to image
    cv::addWeighted(imageROI, 1.0, logo, 0.3, 0.0, imageROI);
    cv::imshow("with logo", image);

    // read images
    image = cv::imread("../images/boldt.jpg");
    logo  = cv::imread("../images/logo.bmp");

    // define image ROI
    imageROI = image(cv::Rect(385, 270, logo.cols, logo.rows));

    // load the mask (must be gray-level)
    cv::Mat mask = cv::imread("../images/logo.bmp", 0);

    // copy to ROI with mask
    logo.copyTo(imageROI, mask);
    cv::imshow("with logo 2", image);

    // read images
    image = cv::imread("../images/boldt.jpg");
    logo  = cv::imread("../images/logo.bmp", 0);

    // split 3-channel image into 3 1-channel images
    std::vector<cv::Mat> channels;
    split(image, channels);

    imageROI = channels.at(1);

    cv::addWeighted(imageROI(cv::Rect(385, 270, logo.cols, logo.rows)), 1.0, logo, 0.5, 0.0,
                    imageROI(cv::Rect(385, 270, logo.cols, logo.rows)));

    cv::merge(channels, image);
    cv::imshow("with logo 3", image);

    cv::waitKey();
    return 0;
}
