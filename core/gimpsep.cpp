#include "gimpsep.h"

#include <iostream>
#include <opencv2/opencv.hpp>

typedef std::string String;

cv::Mat Gimpsep::readImage(const String &filename, int flags = cv::IMREAD_COLOR) {
    cv::Mat image = cv::imread(filename, flags);
    if (image.empty()) {
        std::cout << "Error: Failed to open image" << std::endl;
    }
    return image;
}


void Gimpsep::cannyEdgeDetection(String &inputPath, String &outputPath, double threshold1, double threshold2,
                                 int apertureSize) {
    cv::Mat image = Gimpsep::readImage(inputPath);
    cv::Mat edges;

    cv::Canny(image, edges, threshold1, threshold2, apertureSize);
    cv::imwrite(outputPath, edges);

    std::cout << "Canny edge detection completed!" << std::endl;
}

