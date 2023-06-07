#include "GimpsepVideo.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>

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


void GimpsepVideo::dilate(String &inputPath, String &outputPath, int erosionSize) {
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
}

void GimpsepVideo::erode(String &inputPath, String &outputPath, int erosionSize) {
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
}

void GimpsepVideo::lightenDarken(String &inputPath, String &outputPath, double factor) {
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
}

void GimpsepVideo::cannyEdgeDetection(String &inputPath, String &outputPath, double threshold1, double threshold2,
                                      int apertureSize) {
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
}

void GimpsepVideo::resize(String &inputPath, String &outputPath, int width, int height) {
    cv::VideoCapture cap(inputPath);

    if (!cap.isOpened()) {
        std::cout << "Error: Failed to open video" << std::endl;
    }

    cv::VideoWriter video(outputPath, cap.get(cv::CAP_PROP_FOURCC), cap.get(cv::CAP_PROP_FPS), cv::Size(width, height));

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;

        cv::Mat resizedImage;

        cv::resize(frame, resizedImage, cv::Size(width, height));
        video.write(resizedImage);
    }

    cap.release();
    video.release();

    std::cout << "Resizing completed!" << std::endl;
}

void GimpsepVideo::resize(String &inputPath, String &outputPath, double factor) {
    cv::VideoCapture cap(inputPath);

    if (!cap.isOpened()) {
        std::cout << "Error: Failed to open video" << std::endl;
    }

    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH) * factor);
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT) * factor);

    cv::VideoWriter video(outputPath, cap.get(cv::CAP_PROP_FOURCC), cap.get(cv::CAP_PROP_FPS), cv::Size(width, height));

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;

        cv::Mat resizedImage;

        cv::resize(frame, resizedImage, cv::Size(width, height));
        video.write(resizedImage);
    }
    cap.release();
    video.release();

    std::cout << "Resizing completed!" << std::endl;
}
