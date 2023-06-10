#include "GimpsepVideo.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

//const String CASCADE_MODEL = "/../../assets/models/haarcascade_frontalface.xml";

typedef std::string String;

std::pair<cv::VideoCapture, cv::VideoWriter>
GimpsepVideo::readVideo(const String &filename, const String &outputPath, bool isColor = true) {
    cv::VideoCapture cap(filename);

    if (!cap.isOpened()) {
        std::cout << "Error: Failed to open video" << std::endl;
    }

    cv::VideoWriter video(outputPath, cap.get(cv::CAP_PROP_FOURCC), cap.get(cv::CAP_PROP_FPS),
                          cv::Size(cap.get(cv::CAP_PROP_FRAME_WIDTH), cap.get(cv::CAP_PROP_FRAME_HEIGHT)), isColor);

    //return VideoCapture and VideoWriter objects in a pair
    //to access each element of a pair uses the following syntax
    //std::pair <cv::VideoCapture, cv::VideoWriter> videoCW = Gimpsep::readVideo(inputPath, outputPath);
    //cv::VideoCapture cap = videoCW.first;
    //cv::VideoWriter video = videoCW.second;

    return std::make_pair(cap, video);
}

void GimpsepVideo::showVideos(const String &inputVideo, const String &outputVideo) {
    cv::VideoCapture input(inputVideo);
    cv::VideoCapture output(outputVideo);

    const String inputWindow = "Input Video";
    const String outputWindow = "Output Video";

    cv::namedWindow(inputWindow);
    cv::namedWindow(outputWindow);

    while (true) {
        cv::Mat inputFrame;
        cv::Mat outputFrame;

        input >> inputFrame;
        output >> outputFrame;
        if (inputFrame.empty() && outputFrame.empty())
            break;
        
        cv::imshow(inputWindow, inputFrame);
        cv::imshow(outputWindow, outputFrame);
    }

    cv::waitKey(0);
    cv::destroyAllWindows();
    input.release();
    output.release();
}


void GimpsepVideo::dilate(String &inputPath, String &outputPath, int erosionSize, char verbose) {
    std::pair<cv::VideoCapture, cv::VideoWriter> videoCW = GimpsepVideo::readVideo(inputPath, outputPath);
    cv::VideoCapture cap = videoCW.first;
    cv::VideoWriter video = videoCW.second;

    cv::Mat dilatedImage;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(2 * erosionSize + 1, 2 * erosionSize + 1),
                                                cv::Point(erosionSize, erosionSize));

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;

        cv::dilate(frame, dilatedImage, element);
        video.write(dilatedImage);
    }

    cap.release();
    video.release();
    videoCW.first.release();
    videoCW.second.release();

    std::cout << "Dilated image saved as" << outputPath << std::endl;

    if(verbose == 'y') {
        GimpsepVideo::showVideos(inputPath, outputPath);
    }
}

void GimpsepVideo::erode(String &inputPath, String &outputPath, int erosionSize, char verbose) {
    std::pair<cv::VideoCapture, cv::VideoWriter> videoCW = GimpsepVideo::readVideo(inputPath, outputPath);
    cv::VideoCapture cap = videoCW.first;
    cv::VideoWriter video = videoCW.second;

    cv::Mat erodedImage;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(2 * erosionSize + 1, 2 * erosionSize + 1),
                                                cv::Point(erosionSize, erosionSize));

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;

        cv::erode(frame, erodedImage, element);
        video.write(erodedImage);
    }

    cap.release();
    video.release();
    videoCW.first.release();
    videoCW.second.release();

    std::cout << "Erode image saved as" << outputPath << std::endl;

    if(verbose == 'y') {
        GimpsepVideo::showVideos(inputPath, outputPath);
    }
}

void GimpsepVideo::lightenDarken(String &inputPath, String &outputPath, double factor, char verbose) {
    std::pair<cv::VideoCapture, cv::VideoWriter> videoCW = GimpsepVideo::readVideo(inputPath, outputPath);
    cv::VideoCapture cap = videoCW.first;
    cv::VideoWriter video = videoCW.second;

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;

        cv::Mat brightness;

        frame.convertTo(brightness, -1, 1, factor);
        video.write(brightness);
    }

    cap.release();
    video.release();
    videoCW.first.release();
    videoCW.second.release();

    std::cout << "Brightness adjustment completed!" << std::endl;

    if(verbose == 'y') {
        GimpsepVideo::showVideos(inputPath, outputPath);
    }
}

void GimpsepVideo::cannyEdgeDetection(String &inputPath, String &outputPath, double threshold1, double threshold2,
                                      int apertureSize, char verbose) {
    std::pair<cv::VideoCapture, cv::VideoWriter> videoCW = GimpsepVideo::readVideo(inputPath, outputPath, false);
    cv::VideoCapture cap = videoCW.first;
    cv::VideoWriter video = videoCW.second;

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;

        cv::Mat edges;

        cv::Canny(frame, edges, threshold1, threshold2, apertureSize);
        video.write(edges);
    }

    cap.release();
    video.release();
    videoCW.first.release();
    videoCW.second.release();

    std::cout << "Canny edge detection completed!" << std::endl;

    if(verbose == 'y') {
        GimpsepVideo::showVideos(inputPath, outputPath);
    }
}

void GimpsepVideo::resize(String &inputPath, String &outputPath, int width, int height, char verbose) {
    std::pair<cv::VideoCapture, cv::VideoWriter> videoCW = GimpsepVideo::readVideo(inputPath, outputPath);
    cv::VideoCapture cap = videoCW.first;
    cv::VideoWriter video = videoCW.second;


    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;

        cv::Mat resizedImage;

        cv::resize(frame, resizedImage, cv::Size(width, height),cv::INTER_LINEAR);
        video.write(resizedImage);
    }

    cap.release();
    video.release();
    videoCW.first.release();
    videoCW.second.release();

    std::cout << "Resizing completed!" << std::endl;

    if(verbose == 'y') {
        GimpsepVideo::showVideos(inputPath, outputPath);
    }
}

void GimpsepVideo::resize(String &inputPath, String &outputPath, double factor, char verbose) {
    std::pair<cv::VideoCapture, cv::VideoWriter> videoCW = GimpsepVideo::readVideo(inputPath, outputPath);
    cv::VideoCapture cap = videoCW.first;
    cv::VideoWriter video = videoCW.second;

    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH) * factor);
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT) * factor);

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;

        cv::Mat resizedImage;

        cv::resize(frame, resizedImage, cv::Size(width, height),cv::INTER_LINEAR);
        video.write(resizedImage);
    }
    cap.release();
    video.release();
    videoCW.first.release();
    videoCW.second.release();
    std::cout << "Resizing completed!" << std::endl;

    if(verbose == 'y') {
        GimpsepVideo::showVideos(inputPath, outputPath);
    }
}

void GimpsepVideo::detectAndDraw(cv::CascadeClassifier &cascade, cv::Mat &img) {
    std::vector<cv::Rect> facesCoordinates;
    int frame = 4;
    cv::Scalar color = cv::Scalar(255, 0, 0);

    // turn to grayscale
    cv::Mat gray;
    cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // Detect faces of different sizes using cascade classifier
    cascade.detectMultiScale(gray, facesCoordinates);

    // draw rectangle on coordinates
    for (auto &face: facesCoordinates) {
        cv::rectangle(img, face, color, frame, 1, 0);
    }
}

void GimpsepVideo::gaussianBlur(const std::string& inputPath, const std::string& outputPath, const cv::Size& kernelSize,char verbose) {
    std::pair<cv::VideoCapture, cv::VideoWriter> videoCW = GimpsepVideo::readVideo(inputPath, outputPath);
    cv::VideoCapture cap = videoCW.first;
    cv::VideoWriter video = videoCW.second;

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;
            
        cv::Mat blurredFrame;
        cv::GaussianBlur(frame, blurredFrame, kernelSize, 0);
        video.write(blurredFrame);
    }

    cap.release();
    video.release();
    videoCW.first.release();
    videoCW.second.release();


    std::cout << "Gaussian blur applied to video successfully. Output path: " << outputPath << std::endl;

    if(verbose == 'y') {
        GimpsepVideo::showVideos(inputPath, outputPath);
    }
}


void GimpsepVideo::faceDetection(String &inputPath, String &outputPath, String cascadeModel, char verbose) {
    cv::CascadeClassifier cascade;

    if (!cascade.load(cascadeModel)) {
        std::cout << "Error loading face detection cascade model!" << std::endl;
    }

    std::pair<cv::VideoCapture, cv::VideoWriter> videoCW = GimpsepVideo::readVideo(inputPath, outputPath);
    cv::VideoCapture cap = videoCW.first;
    cv::VideoWriter video = videoCW.second;

    if (cap.isOpened()) {
        std::cout << "Starting face detection.." << std::endl;

        while (true) {
            cv::Mat frame;
            cap >> frame;
            if (frame.empty())
                break;

            GimpsepVideo::detectAndDraw(cascade, frame);
            video.write(frame);
        }

        cap.release();
        video.release();
        videoCW.first.release();
        videoCW.second.release();

        std::cout << "Face detection video saved as " << outputPath << std::endl;
    } else {
        std::cout << "Video could not be opened!" << std::endl;
    }

    if(verbose == 'y') {
        GimpsepVideo::showVideos(inputPath, outputPath);
    }
}
