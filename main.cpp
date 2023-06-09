#include "core/Gimpsep.h"
#include "core/GimpsepVideo.h"
#include "utils/FileReader.h"

#include <iostream>
#include <vector>


typedef std::string String;

const String WELCOME_TEXT_FILE_PATH = "../assets/welcome.txt";
const String CASCADE_MODEL = "../assets/models/haarcascade_frontalface.xml";

void displayLogo();

void help();

int main() {
    displayLogo();

    while (true) {
        std::cout << "Enter an option or 'q' to quit: ";

        String option;
        std::getline(std::cin, option);

        if (option == "q") {
            break;
        }

        if (option == "--help") {
            help();
        } else if (option == "--dilate" || option == "--dilate --video") {
            String inputPath, outputPath;
            int dilationSize;
            char verbose;

            std::cout << "Enter input path: ";
            std::getline(std::cin, inputPath);
            std::cout << "Enter output path: ";
            std::getline(std::cin, outputPath);
            std::cout << "Enter dilation size: ";
            std::cin >> dilationSize;
            std::cout << "Display before/after? (y/n): ";
            std::cin >> verbose;
            std::cin.ignore(); // Ignore remaining newline character

            if (option == "--dilate") {
                Gimpsep::dilate(inputPath, outputPath, dilationSize, verbose);
            } else {
                GimpsepVideo::dilate(inputPath, outputPath, dilationSize, verbose);
            }
        } else if (option == "--erode" || option == "--erode --video") {
            String inputPath, outputPath;
            int erosionSize;
            char verbose;

            std::cout << "Enter input path: ";
            std::getline(std::cin, inputPath);
            std::cout << "Enter output path: ";
            std::getline(std::cin, outputPath);
            std::cout << "Enter erosion size: ";
            std::cin >> erosionSize;
            std::cout << "Display before/after? (y/n): ";
            std::cin >> verbose;
            std::cin.ignore(); // Ignore remaining newline character

            if (option == "--erode") {
                Gimpsep::erode(inputPath, outputPath, erosionSize, verbose);
            } else {
                GimpsepVideo::erode(inputPath, outputPath, erosionSize, verbose);
            }
        } else if (option == "--resize" || option == "--resize --video") {
            String inputPath, outputPath;
            int width, height;
            char verbose;

            std::cout << "Enter input path: ";
            std::getline(std::cin, inputPath);
            std::cout << "Enter output path: ";
            std::getline(std::cin, outputPath);
            std::cout << "Enter width: ";
            std::cin >> width;
            std::cout << "Enter height: ";
            std::cin >> height;
            std::cout << "Display before/after? (y/n): ";
            std::cin >> verbose;
            std::cin.ignore(); // Ignore remaining newline character

            if (option == "--resize") {
                Gimpsep::resizeImage(inputPath, outputPath, width, height, verbose);
            } else {
                GimpsepVideo::resize(inputPath, outputPath, width, height, verbose);
            }
        } else if (option == "--resize-by-factor" || option == "--resize-by-factor --video") {
            String inputPath, outputPath;
            double factor;
            char verbose;

            std::cout << "Enter input path: ";
            std::getline(std::cin, inputPath);
            std::cout << "Enter output path: ";
            std::getline(std::cin, outputPath);
            std::cout << "Enter factor: ";
            std::cin >> factor;
            std::cout << "Display before/after? (y/n): ";
            std::cin >> verbose;
            std::cin.ignore(); // Ignore remaining newline character

            if (option == "--resize") {
                Gimpsep::resizeImage(inputPath, outputPath, factor, verbose);
            } else {
                GimpsepVideo::resize(inputPath, outputPath, factor, verbose);
            }
        } else if (option == "--lighten-darken" || option == "--lighten-darken --video") {
            String inputPath, outputPath;
            double factor;
            char verbose;

            std::cout << "Enter input path: ";
            std::getline(std::cin, inputPath);
            std::cout << "Enter output path: ";
            std::getline(std::cin, outputPath);
            std::cout << "Enter factor: ";
            std::cin >> factor;
            std::cout << "Display before/after? (y/n): ";
            std::cin >> verbose;
            std::cin.ignore(); // Ignore remaining newline character

            if (option == "--lighten-darken") {
                Gimpsep::lightenDarken(inputPath, outputPath, factor, verbose);
            } else {
                GimpsepVideo::lightenDarken(inputPath, outputPath, factor, verbose);
            }
        } else if (option == "--canny" || option == "--canny --video") {
            String inputPath, outputPath;
            double threshold1, threshold2;
            int apertureSize;
            char verbose;

            std::cout << "Enter input path: ";
            std::getline(std::cin, inputPath);
            std::cout << "Enter output path: ";
            std::getline(std::cin, outputPath);
            std::cout << "Enter threshold 1: ";
            std::cin >> threshold1;
            std::cout << "Enter threshold 2: ";
            std::cin >> threshold2;
            std::cout << "Enter aperture size: ";
            std::cin >> apertureSize;
            std::cout << "Display before/after? (y/n): ";
            std::cin >> verbose;
            std::cin.ignore(); // Ignore remaining newline character

            if (option == "--canny") {
                Gimpsep::cannyEdgeDetection(inputPath, outputPath, threshold1, threshold2, apertureSize, verbose);
            } else {
                GimpsepVideo::cannyEdgeDetection(inputPath, outputPath, threshold1, threshold2, apertureSize, verbose);
            }
        } else if (option == "--panorama") {
            String outputPath;
            char verbose;

            std::cout << "Enter output path: ";
            std::getline(std::cin, outputPath);
            std::vector<String> inputPaths;
            std::cout << "Enter input paths (separated by spaces): ";
            String input;
            std::getline(std::cin, input);
            std::cout << "Display before/after? (y/n): ";
            std::cin >> verbose;

            // Split the input string into individual paths
            std::istringstream iss(input);
            std::string path;
            while (iss >> path) {
                inputPaths.push_back(path);
            }

            Gimpsep::stitch(&inputPaths, outputPath, verbose);
        } else if (option == "--detect" || option == "--detect --video") {
            String inputPath, outputPath;
            char verbose;

            std::cout << "Enter input path: ";
            std::getline(std::cin, inputPath);
            std::cout << "Enter output path: ";
            std::getline(std::cin, outputPath);
            std::cout << "Display before/after? (y/n): ";
            std::cin >> verbose;
            std::cin.ignore(); // Ignore remaining newline character

            if (option == "--detect") {
                Gimpsep::faceDetection(inputPath, outputPath, CASCADE_MODEL, verbose);
            } else {
                GimpsepVideo::faceDetection(inputPath, outputPath, CASCADE_MODEL, verbose);
            }
        } else {
            std::cout << "Invalid option! Enter '--help' to see the available options." << std::endl;
        }
    }

    return 0;
}

void displayLogo() {
    std::string asciiArt = FileReader::readTextFile(WELCOME_TEXT_FILE_PATH);
    std::cout << asciiArt << std::endl;
}

void help() {
    std::cout << "Usage of GIMPSEP-C-IMP:" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --dilate [--video]: Perform dilatation" << std::endl;
    std::cout << "  --erode [--video]: Perform erosion" << std::endl;
    std::cout << "  --resize [--video]: Resize image/video" << std::endl;
    std::cout << "  --resize-by-factor [--video]: Resize image/video by factor" << std::endl;
    std::cout << "  --lighten-darken [--video]: Lighten or darken the image/video" << std::endl;
    std::cout << "  --canny [--video]: Perform Canny edge detection" << std::endl;
    std::cout << "  --panorama: Create a panorama by stitching images" << std::endl;
    std::cout << "  --help: Show help information" << std::endl;
}
