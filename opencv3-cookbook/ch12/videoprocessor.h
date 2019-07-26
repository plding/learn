#ifndef VIDEO_PROCESSOR_H
#define VIDEO_PROCESSOR_H

class VideoProcessor {

private:
    // the OpenCV video capture object
    cv::VideoCapture capture;
    // the callback function to be called for the processing of each frame
    void (*process)(cv::Mat &, cv::Mat &);
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
        return capture.read(frame);
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
    bool setInput(std::string filename) { return capture.open(filename); }

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
    double getFrameRate() { return capture.get(cv::CAP_PROP_FPS); } 

    // return the size of the video frame
    cv::Size getFrameSize()
    {
        int w = static_cast<int>(capture.get(cv::CAP_PROP_FRAME_WIDTH));
        int h = static_cast<int>(capture.get(cv::CAP_PROP_FRAME_HEIGHT));

        return cv::Size(w, h);
    }

    // get the codec of input video
    int getCodec(char codec[4])
    {
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

    // Stop the processing
    void stopIt() { stop = true; }

    // Is the process stopped?
    bool isStopped() { return stop; }

    // Is a capture device opened?
    bool isOpened() { return capture.isOpened(); }

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
            if (process) {
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
