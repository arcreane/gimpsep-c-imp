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

public:
    static void dilate(String &inputPath, String &outputPath, int erosionSize);

    static void erode(String &inputPath, String &outputPath, int erosionSize);

    static void resize(String &inputPath, String &outputPath, int width, int height);

    static void resize(String &inputPath, String &outputPath, double factor);

    static void lightenDarken(String &inputPath, String &outputPath, double factor);

    static void cannyEdgeDetection(String &inputPath, String &outputPath, double threshold1, double threshold2,
                                   int apertureSize);
};

#endif
