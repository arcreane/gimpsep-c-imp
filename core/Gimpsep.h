#ifndef GIMPSEP_C_IMP_GIMPSEP_H
#define GIMPSEP_C_IMP_GIMPSEP_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

typedef std::string String;

class Gimpsep {
private:
    static cv::Mat readImage(const String &filename, int flags);
    static void showImages(cv::Mat inputImage, cv::Mat outputImage);

public:
    static void dilate(String &inputPath, String &outputPath, int erosionSize, char verbose);

    static void erode(String &inputPath, String &outputPath, int erosionSize, char verbose);

    static void resizeImage(String &inputPath, String &outputPath, int width, int height, char verbose);

    static void resizeImage(String &inputPath, String &outputPath, double factor, char verbose);

    static void lightenDarken(String &inputPath, String &outputPath, double factor, char verbose);

    static void stitch(std::vector<String> *inputPaths, String &outputPath, char verbose);

    static void
    cannyEdgeDetection(String &inputPath, String &outputPath, double threshold1, double threshold2, int apertureSize, char verbose);

    static void faceDetection(String &inputPath, String &outputPath, String cascadeModel, char verbose);
    
    static void gaussianBlur(String& inputPath, String& outputPath, cv::Size kernelSize, char verbose);

};

#endif
