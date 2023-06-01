#ifndef GIMPSEP_C_IMP_GIMPSEP_H
#define GIMPSEP_C_IMP_GIMPSEP_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

typedef std::string String;

class Gimpsep {
private:
    static cv::Mat readImage(const String &filename, int flags);
    static std::pair<cv::VideoCapture, cv::VideoWriter> readVideo(const String &filename, const String &outputPath, bool isColor);

public:
    static void dilate(String &inputPath, String &outputPath, int erosionSize);

    static void erode(String &inputPath, String &outputPath, int erosionSize);

    static void resizeImage(String &inputPath, String &outputPath, int width, int height);

    static void resizeImage(String &inputPath, String &outputPath, double factor);

    static void lightenDarken(String &inputPath, String &outputPath, double factor);

    static void stitch(std::vector<String> *inputPaths, String &outputPath);

    static void
    cannyEdgeDetection(String &inputPath, String &outputPath, double threshold1, double threshold2, int apertureSize);

    static void dilateVideo(String &inputPath, String &outputPath, int erosionSize);

    static void erodeVideo(String &inputPath, String &outputPath, int erosionSize);

    static void resizeVideo(String &inputPath, String &outputPath, int width, int height);

    static void resizeVideo(String &inputPath, String &outputPath, double factor);

    static void lightenDarkenVideo(String &inputPath, String &outputPath, double factor);

    static void
    cannyEdgeDetectionVideo(String &inputPath, String &outputPath, double threshold1, double threshold2, int apertureSize);

};

#endif //GIMPSEP_C_IMP_GIMPSEP_H
