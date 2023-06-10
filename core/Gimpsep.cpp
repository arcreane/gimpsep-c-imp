#include "Gimpsep.h"
#include "GimpsepVideo.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

typedef std::string String;

cv::Mat Gimpsep::readImage(const String &filename, int flags = cv::IMREAD_COLOR) {
    cv::Mat image = cv::imread(filename, flags);
    if (image.empty()) {
        std::cout << "Error: Failed to open image" << std::endl;
    }
    return image;
}

void Gimpsep::showImages(cv::Mat inputImage, cv::Mat outputImage) {
    cv::imshow("Input Image", inputImage);
    cv::imshow("Output Image", outputImage);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

void Gimpsep::cannyEdgeDetection(String &inputPath, String &outputPath, double threshold1, double threshold2,
                                 int apertureSize, char verbose) {
    cv::Mat image = Gimpsep::readImage(inputPath);
    cv::Mat edges;

    cv::Canny(image, edges, threshold1, threshold2, apertureSize);
    cv::imwrite(outputPath, edges);

    std::cout << "Canny edge detection completed!" << std::endl;

    if(verbose == 'y') {
        Gimpsep::showImages(image, edges);
    }
}

void Gimpsep::dilate(String &inputPath, String &outputPath, int size, char verbose) {
    cv::Mat image = Gimpsep::readImage(inputPath);
    cv::Mat dilatedImage;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(2 * size + 1, 2 * size + 1),
                                                cv::Point(size, size));
    cv::dilate(image, dilatedImage, element);
    cv::imwrite(outputPath, dilatedImage);
    std::cout << "Dilated image saved as" << outputPath << std::endl;

    if(verbose == 'y') {
        Gimpsep::showImages(image, dilatedImage);
    }
}


void Gimpsep::erode(String &inputPath, String &outputPath, int size, char verbose) {
    cv::Mat image = Gimpsep::readImage(inputPath);
    cv::Mat erodedImage;

    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(2 * size + 1, 2 * size + 1),
                                                cv::Point(size, size));
    cv::erode(image, erodedImage, element);
    cv::imwrite(outputPath, erodedImage);
    std::cout << "Erode image saved as" << outputPath << std::endl;

    if(verbose == 'y') {
        Gimpsep::showImages(image, erodedImage);
    }
}

void Gimpsep::resizeImage(String &inputPath, String &outputPath, int width, int height, char verbose) {
    cv::Mat image = Gimpsep::readImage(inputPath);
    cv::Mat resizedImage;

    cv::resize(image, resizedImage, cv::Size(width, height));
    cv::imwrite(outputPath, resizedImage);

    std::cout << "Resized image saved as" << outputPath << std::endl;

    if(verbose == 'y') {
        Gimpsep::showImages(image, resizedImage);
    }
}

void Gimpsep::resizeImage(String &inputPath, String &outputPath, double factor, char verbose) {
    cv::Mat image = Gimpsep::readImage(inputPath);
    cv::Mat resizedImage;

    cv::resize(image, resizedImage, cv::Size(image.rows * factor, image.cols * factor));
    cv::imwrite(outputPath, resizedImage);

    std::cout << "Resized image saved as" << outputPath << std::endl;

    if(verbose == 'y') {
        Gimpsep::showImages(image, resizedImage);
    }
}

void Gimpsep::lightenDarken(String &inputPath, String &outputPath, double factor, char verbose) {
    cv::Mat image = Gimpsep::readImage(inputPath);
    cv::Mat brightness;

    image.convertTo(brightness, image.type(), 1, factor);
    cv::imwrite(outputPath, brightness);

    std::cout << "Brightness adjustment completed!" << std::endl;

    if(verbose == 'y') {
        Gimpsep::showImages(image, brightness);
    }
}

void Gimpsep::stitch(std::vector<String> *inputPaths, String &outputPath, char verbose) {
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

    if(verbose == 'y') {
        for (int i = 0; i < image_array.size(); i++) {
            String windowName = "Input Image " + std::to_string(i+1);
            cv::imshow(windowName, image_array[i]);
        }
        cv::imshow("Output Image", pano);
        cv::waitKey(0);
        cv::destroyAllWindows();
    }
}

void Gimpsep::faceDetection(String &inputPath, String &outputPath, String cascadeModel, char verbose){
    cv::CascadeClassifier cascade;
    if (!cascade.load(cascadeModel)) {
        std::cout << "Error loading face detection cascade model!" << std::endl;
    }

    cv::Mat image = Gimpsep::readImage(inputPath);
    cv::Mat faces = image.clone();

    GimpsepVideo::detectAndDraw(cascade, faces);
    cv::imwrite(outputPath, faces);
    std::cout << "Face detection for picture completed!" << std::endl;

    if(verbose == 'y') {
        Gimpsep::showImages(image, faces);
    }
}
void Gimpsep::gaussianBlur(String& inputPath, String& outputPath, cv::Size kernelSize,char verbose)
{
    cv::Mat source = cv::imread(inputPath);
    if (source.empty()) {
        std::cout << "Could not find or open the image" << std::endl;
        return;
    }

    cv::Mat blurredImage;
    cv::GaussianBlur(source, blurredImage, kernelSize, 0);

    cv::imwrite(outputPath, blurredImage);
    std::cout << "Gaussian blur applied to the image!" << std::endl;

    if(verbose == 'y') {
        Gimpsep::showImages(source, blurredImage);
    }
}

