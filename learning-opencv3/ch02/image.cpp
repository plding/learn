#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <image_path>" << std::endl;
        return 0;
    }

    cv::Mat img = cv::imread(argv[1], -1);
    if (img.empty()) return -1;

    cv::imshow("Image", img);
    cv::waitKey(0);

    return 0;
}
