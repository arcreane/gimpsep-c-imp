#include "Gimpsep.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>

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

void Gimpsep::dilate(String &inputPath, String &outputPath, int size) {
    cv::Mat image = Gimpsep::readImage(inputPath);
    cv::Mat dilatedImage;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(2 * size + 1, 2 * size + 1),
                                                cv::Point(size, size));
    cv::dilate(image, dilatedImage, element);
    cv::imwrite(outputPath, dilatedImage);
    std::cout << "Dilated image saved as" << outputPath << std::endl;
}


void Gimpsep::erode(String &inputPath, String &outputPath, int size) {
    cv::Mat image = Gimpsep::readImage(inputPath);
    cv::Mat erodedImage;

    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(2 * size + 1, 2 * size + 1),
                                                cv::Point(size, size));
    cv::erode(image, erodedImage, element);
    cv::imwrite(outputPath, erodedImage);
    std::cout << "Erode image saved as" << outputPath << std::endl;
}

void Gimpsep::resizeImage(String &inputPath, String &outputPath, int width, int height) {
    cv::Mat image = Gimpsep::readImage(inputPath);
    cv::Mat resizedImage;

    cv::resize(image, resizedImage, cv::Size(width, height));
    cv::imwrite(outputPath, resizedImage);

    std::cout << "Resized image saved as" << outputPath << std::endl;
}

void Gimpsep::resizeImage(String &inputPath, String &outputPath, double factor) {
    cv::Mat image = Gimpsep::readImage(inputPath);
    cv::Mat resizedImage;

    cv::resize(image, resizedImage, cv::Size(image.rows * factor, image.cols * factor));
    cv::imwrite(outputPath, resizedImage);

    std::cout << "Resized image saved as" << outputPath << std::endl;
}

void Gimpsep::lightenDarken(String &inputPath, String &outputPath, double factor) {
    cv::Mat image = Gimpsep::readImage(inputPath);
    cv::Mat brightness;

    image.convertTo(brightness, image.type(), 1, factor);
    cv::imwrite(outputPath, brightness);

    std::cout << "Brightness adjustment completed!" << std::endl;
}

void Gimpsep::stitch(std::vector<String> *inputPaths, String &outputPath) {
    std::vector<cv::Mat> image_array;
    for (int i = 0; i < inputPaths->size(); i++) {
        image_array.emplace_back(Gimpsep::readImage((*inputPaths)[i]));
    }

    cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
    cv::Mat pano;

    cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);

    cv::Stitcher::Status status = stitcher->stitch(image_array, pano);

    if (status == cv::Stitcher::ERR_NEED_MORE_IMGS) {
        std::cout << "Need more images." << std::endl;
        return;
    } else if (status == cv::Stitcher::ERR_CAMERA_PARAMS_ADJUST_FAIL) {
        std::cout << "Camera parameter adjustment failed." << std::endl;
        return;
    } else if (status == cv::Stitcher::ERR_HOMOGRAPHY_EST_FAIL) {
        std::cout << "Homography estimation failed." << std::endl;
        return;
    }

    cv::imwrite(outputPath, pano);

    std::cout << "Panorama created!" << std::endl;
}
