#ifndef VIDEO_PROCESSOR_H
#define VIDEO_PROCESSOR_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

// The frame processor interface
class FrameProcessor {

public:
    virtual void process(cv::Mat &input, cv::Mat &output) = 0;
};

class VideoProcessor {

private:
    // the OpenCV video capture object
    cv::VideoCapture capture;
    
    // vector of image filename to be used as input
    std::vector<std::string> images;
    // image vector iterator
    std::vector<std::string>::const_iterator itImg;
    
    // the callback function to be called for the processing of each frame
    void (*process)(cv::Mat &, cv::Mat &);
    // the pointer to the class implementing the FrameProcessor interface
    FrameProcessor *frameProcessor;
    
    // Input display window name
    std::string windowNameInput;
    // Output display window name
    std::string windowNameOutput;

    // delay between each frame processing
    int delay;
    // to stop the processing
    bool stop;

    // the OpenCV video writer object
    cv::VideoWriter writer;
    // output filename
    std::string outputFile;

    // to get the next frame
    bool readNextFrame(cv::Mat &frame)
    {
        if (capture.isOpened()) {
            return capture.read(frame);
        }

        if (itImg != images.end()) {
            frame = cv::imread(*itImg++);
            return !frame.empty();
        }

        return false;
    }

    // to write the output frame
    void writeNextFrame(cv::Mat &frame)
    {
        writer.write(frame);
    }

public:
    // Constructor
    VideoProcessor() : delay(-1), stop(false) {}

    // set the name of the video file 
    bool setInput(std::string filename)
    {
        images.clear();
        return capture.open(filename);
    }

    // set the vector of input images
    bool setInput(const std::vector<std::string> &imgs)
    {
        capture.release();
        
        images = imgs;
        itImg = images.begin();

        return true;
    }

    // set the output video file
    bool setOutput(const std::string &filename, int codec = 0, double fps = 0.0,
                   bool isColor = true)
    {
        outputFile = filename;

        if (fps == 0.0) {
            fps = getFrameRate();
        }

        if (codec == 0) {
            char c[4];
            codec = getCodec(c);
        }

        cv::Size frameSize = getFrameSize();

        // Open output video
        return writer.open(outputFile,  // Name of the output video file
                           codec,       // 4-character code of codec used to compress the frames
                           fps,         // Framerate of the created video stream 
                           frameSize,   // Size of the video frames
                           isColor);    // If it not zero, the encoder will expect and encode color 
                                        // frames, otherwise it will work with grayscale frames
    }

    // to display the input frames
    void displayInput(std::string name) { windowNameInput = name; }

    // to display the output frames
    void displayOutput(std::string name) { windowNameOutput = name; }

    // return the frame rate
    double getFrameRate()
    {
        if (images.size() == 0) {
            return 0;
        }

        return capture.get(cv::CAP_PROP_FPS);
    } 

    // return the size of the video frame
    cv::Size getFrameSize()
    {
        if (images.size() == 0) {
            return cv::Size(static_cast<int>(capture.get(cv::CAP_PROP_FRAME_WIDTH)),
                            static_cast<int>(capture.get(cv::CAP_PROP_FRAME_HEIGHT)));
        }

        cv::Mat tmp = cv::imread(images[0]);
        if (!tmp.empty()) {
            return tmp.size();
        }

        return cv::Size(0, 0);
    }

    // get the codec of input video
    int getCodec(char codec[4])
    {
        if (images.size() != 0) {
            return -1;
        }

        union {
            int value;
            char code[4];
        } returned;

        returned.value = static_cast<int>(capture.get(cv::CAP_PROP_FOURCC));

        codec[0] = returned.code[0];
        codec[1] = returned.code[1];
        codec[2] = returned.code[2];
        codec[3] = returned.code[3];

        return returned.value;
    }

    // set a delay between each frame
    void setDelay(int d) { delay = d; }

    // set the callback function that will be called for each frame
    void setFrameProcessor(void (*frameProcessorCallback)(cv::Mat &, cv::Mat &))
    {
        process = frameProcessorCallback;
    }

    // set the instance of the class that implements the FrameProcessor interface
    void setFrameProcessor(FrameProcessor *frameProcessorPtr)
    {
        frameProcessor = frameProcessorPtr;
    }

    // Stop the processing
    void stopIt() { stop = true; }

    // Is the process stopped?
    bool isStopped() { return stop; }

    // Is a capture device opened?
    bool isOpened() { return capture.isOpened() || images.size() != 0; }

    // to grab (and process) the frame of the sequence
    void run()
    {
        // current frame
        cv::Mat frame;
        // output frame
        cv::Mat output;

        // if no capture device has been set
        if (!isOpened()) {
            return;
        }

        stop = false;

        while (!isStopped()) {
            // read next frame if any
            if (!readNextFrame(frame)) {
                break;
            }

            // display input frame
            if (windowNameInput.length() != 0) {
                cv::imshow(windowNameInput, frame);
            }

            // calling the process function or method
            if (frameProcessor) {
                frameProcessor->process(frame, output);
            } else if (process) {
                process(frame, output);
            } else {
                output = frame;
            }

            // write output sequence
            if (outputFile.length() != 0) {
                writeNextFrame(output);
            }

            // display output frame
            if (windowNameOutput.length() != 0) {
                cv::imshow(windowNameOutput, output);
            }

            // introduce a delay
            if (delay >= 0 && cv::waitKey(delay) >= 0) {
                stopIt();
            }
        }
    }
};

#endif /* VIDEO_PROCESSOR_H */
