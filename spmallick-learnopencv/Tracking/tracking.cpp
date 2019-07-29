#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

using namespace cv;
using namespace std;

#define SSTR(x) static_cast<std::ostringstream &>(std::ostringstream() << std::dec << x).str()

int main(int argc, char **argv)
{
    // List of tracker types in OpenCV 3.2
    string trackerTypes[7] = {"BOOSTING", "MIL", "KCF", "TLD", "MEDIANFLOW", "GOTURN", "CSRT"};

    // Create a tracker
    Ptr<Tracker> tracker;
    string trackerType = trackerTypes[argc == 2 ? atoi(argv[1]) : 2];
    if      (trackerType == "BOOSTING")   tracker = TrackerBoosting::create();
    else if (trackerType == "MIL")        tracker = TrackerMIL::create();
    else if (trackerType == "KCF")        tracker = TrackerKCF::create();
    else if (trackerType == "TLD")        tracker = TrackerTLD::create();
    else if (trackerType == "MEDIANFLOW") tracker = TrackerMedianFlow::create();
    else if (trackerType == "GOTURN")     tracker = TrackerGOTURN::create();
    else if (trackerType == "CSRT")       tracker = TrackerCSRT::create();

    // Read video
    VideoCapture video("chaplin.mp4");

    // Exit if video is not opened
    if (!video.isOpened()) {
        cerr << "Could not read video file" << endl;
        return 1;
    }
    
    // Read first frame
    Mat frame;
    bool ok = video.read(frame);

    // Define initial bounding box
    Rect2d bbox(287, 23, 86, 320);

    // Uncomment the line below to select a different bounding box
    bbox = selectROI(frame, false);

    // Display bounding box
    rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
    imshow("Tracking", frame);

    tracker->init(frame, bbox);

    while (video.read(frame)) {
        // Start timer
        double timer = (double) getTickCount();

        // Update the tracking result
        bool ok = tracker->update(frame, bbox);

        // Calculate Frames per seconds (FPS)
        float fps = getTickFrequency() / ((double) getTickCount() - timer);

        if (ok) {
            // Tracking success: Draw the tracked object
            rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
        } else {
            // Tracking failure detected
            putText(frame, "Tracking failure detected", Point(100, 80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
        }

        // Display tracker type on frame
        putText(frame, trackerType + " Tracker", Point(100, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

        // Display FPS on frame
        putText(frame, "FPS: " + SSTR(int(fps)), Point(100, 50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

        // Display frame
        imshow("Tracking", frame);

        // Exit if ESC pressed
        if (waitKey(1) == 27) {
            break;
        }
    }
}
