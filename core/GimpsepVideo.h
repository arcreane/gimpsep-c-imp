#ifndef GIMPSEP_C_IMP_GIMPSEPVIDEO_H
#define GIMPSEP_C_IMP_GIMPSEPVIDEO_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

typedef std::string String;

class GimpsepVideo {
private:
    static std::pair<cv::VideoCapture, cv::VideoWriter>
    readVideo(const String &filename, const String &outputPath, bool isColor);
    static void showVideos(const String &inputVideo, const String &outputVideo);

public:
    static void dilate(String &inputPath, String &outputPath, int erosionSize, char verbose);

    static void erode(String &inputPath, String &outputPath, int erosionSize, char verbose);

    static void resize(String &inputPath, String &outputPath, int width, int height, char verbose);

    static void resize(String &inputPath, String &outputPath, double factor, char verbose);

    static void lightenDarken(String &inputPath, String &outputPath, double factor, char verbose);

    static void cannyEdgeDetection(String &inputPath, String &outputPath, double threshold1, double threshold2,
                                   int apertureSize, char verbose);

    static void faceDetection(String &inputPath, String &outputPath, String cascadeModel, char verbose);

    static void detectAndDraw(cv::CascadeClassifier &cls, cv::Mat &img);        
    
    static void gaussianBlur(const std::string& inputPath, const std::string& outputPath,
                             const cv::Size& kernelSize);
};

#endif
