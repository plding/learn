#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <cmath>
#include <vector>
#include <iostream>

int main()
{
    cv::Mat image = cv::imread("../resources/road.jpg", 0);
    cv::imshow("Original Image", image);

    cv::Mat edges;
    cv::Canny(image, edges, 125, 350);
    cv::imshow("Edges", edges);
    
    cv::Mat result = image.clone();

    // SHT: Standard Hough Transform
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(edges,       // Input single channel image
                   lines,       // N-by-1 two-channel array
                   1,           // rho resolution (pixels)
                   M_PI / 180,  // theta resolution (radians)
                   60);         // Unnormalized accumulator threshold

    std::cout << "SHT Found " << lines.size() << " line(s)" << std::endl;
    for (auto it = lines.begin(); it != lines.end(); ++it) {
        double rho   = (*it)[0];
        double theta = (*it)[1];

        cv::Point p1, p2;
        if (theta < M_PI / 4 || theta > 3 * M_PI / 4) {
            p1 = cv::Point(rho / cos(theta), 0);
            p2 = cv::Point((rho - result.rows * sin(theta)) / cos(theta), result.rows);
        } else {
            p1 = cv::Point(0, rho / sin(theta));
            p2 = cv::Point(result.cols, (rho - result.cols * cos(theta)) / sin(theta));
        }

        cv::line(result, p1, p2, cv::Scalar::all(255), 1);
    }
    cv::imshow("SHT Lines", result);

    // MHT: Multiscale Hough Transform
    cv::HoughLines(edges,
                   lines,
                   1,
                   M_PI / 180,
                   60,
                   10,
                   10 * M_PI / 180);

    std::cout << "MHT Found " << lines.size() << " line(s)" << std::endl;
    image.copyTo(result);

    for (auto it = lines.begin(); it != lines.end(); ++it) {
        double rho   = (*it)[0];
        double theta = (*it)[1];

        cv::Point p1, p2;
        if (theta < M_PI / 4 || theta > 3 * M_PI / 4) {
            p1 = cv::Point(rho / cos(theta), 0);
            p2 = cv::Point((rho - result.rows * sin(theta)) / cos(theta), result.rows);
        } else {
            p1 = cv::Point(0, rho / sin(theta));
            p2 = cv::Point(result.cols, (rho - result.cols * cos(theta)) / sin(theta));
        }

        cv::line(result, p1, p2, cv::Scalar::all(255), 1);
    }
    cv::imshow("MHT Lines", result);

    // PPHT: progressive probabilistic Hough transform
    std::vector<cv::Vec4i> lines2;
    cv::HoughLinesP(edges,          // Input single channel image
                    lines2,         // N-by-1 4-channel array
                    1,              // rho resolution (pixels)
                    M_PI / 180,     // theta resolution (radians)
                    60,             // Unnormalized accumulator threshold
                    10,             // required line length
                    20);            // required line separation

    std::cout << "PPHT found " << lines2.size() << " line(s)" << std::endl;
    image.copyTo(result);

    for (auto it = lines2.begin(); it != lines2.end(); ++it) {
        cv::line(result, cv::Point((*it)[0], (*it)[1]), cv::Point((*it)[2], (*it)[3]),
                 cv::Scalar::all(255), 1); 
    }
    cv::imshow("PPHT Lines", result);

    // HoughCircles
    image = cv::imread("../resources/chariot.jpg", 0);
    cv::imshow("HoughCircles Original Image", image);

    cv::GaussianBlur(image, image, cv::Size(5, 5), 1.5);

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(image,                 // Input single channel image
                     circles,               // N-by-1 3-channel or vector of Vec3f
                     cv::HOUGH_GRADIENT,    // Always cv::HOUGH_GRADIENT
                     2,                     // accumulator resolution (ratio)
                     50,                    // Required sepration (between lines)
                     200,                   // Upper Canny threshold
                     100,                   // Unnormalized accumulator threshold
                     25,                    // Smallest radius to consider
                     100);                  // Largest radius to consider

    std::cout << "Found " << circles.size() << " circle(s)" << std::endl;

    for (auto it = circles.begin(); it != circles.end(); ++it) {
        cv::circle(image, cv::Point((*it)[0], (*it)[1]), (*it)[2], cv::Scalar::all(255), 2);
    }
    cv::imshow("Hough Circles", image);

    cv::waitKey();
    return 0;
}
