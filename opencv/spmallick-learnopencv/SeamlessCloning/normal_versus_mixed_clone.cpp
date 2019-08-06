#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // Read images: src image will be cloned into dst
    Mat src = imread("images/iloveyouticket.jpg");
    Mat dst = imread("images/wood-texture.jpg");

    // Create an all white mask
    Mat src_mask = 255 * Mat::ones(src.rows, src.cols, src.depth());

    // The location of the center of the src in the dst
    Point center(dst.cols / 2, dst.rows / 2);

    // Seamlessly clone src into dst and put the results in output
    Mat normal_clone;
    Mat mixed_clone;

    seamlessClone(src, dst, src_mask, center, normal_clone, NORMAL_CLONE);
    seamlessClone(src, dst, src_mask, center, mixed_clone, MIXED_CLONE);

    // Show results
    imshow("Normal Clone", normal_clone);
    imshow("Mixed Clone", mixed_clone);
    
    waitKey();
    return 0;
}
