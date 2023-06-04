#include <iostream>
#include <vector>

#include "core/gimpsep.h"

typedef std::string String;


void help();

int main(int argc, char **argv) {
    if (argc <= 2) {
        help();
        return 1;
    } else {
        String option = argv[1];

        if (option == "--dilate" && argc == 5) {
            String inputPath = argv[2];
            String outputPath = argv[3];
            int dilationSize = std::stoi(argv[4]);
            Gimpsep::dilate(inputPath, outputPath, dilationSize);
        } else if (option == "--dilate" && argc == 6 && String(argv[2]) == "--video") {
            String inputPath = argv[3];
            String outputPath = argv[4];
            int dilationSize = std::stoi(argv[5]);
            Gimpsep::dilateVideo(inputPath, outputPath, dilationSize);
        } else if (option == "--erode" && argc == 5) {
            String inputPath = argv[2];
            String outputPath = argv[3];
            int erosionSize = std::stoi(argv[4]);
            Gimpsep::erode(inputPath, outputPath, erosionSize);
        } else if (option == "--erode" && argc == 6 && String(argv[2]) == "--video") {
            String inputPath = argv[3];
            String outputPath = argv[4];
            int erosionSize = std::stoi(argv[5]);
            Gimpsep::erodeVideo(inputPath, outputPath, erosionSize);
        } else if (option == "--resize" && argc == 6 && String(argv[2]) != "--video") {
            String inputPath = argv[2];
            String outputPath = argv[3];
            int width = std::stoi(argv[4]);
            int height = std::stoi(argv[5]);
            Gimpsep::resizeImage(inputPath, outputPath, width, height);
        } else if (option == "--resize" && argc == 7 && String(argv[2]) == "--video") {
            String inputPath = argv[3];
            String outputPath = argv[4];
            int width = std::stoi(argv[5]);
            int height = std::stoi(argv[6]);
            Gimpsep::resizeVideo(inputPath, outputPath, width, height);
        } else if (option == "--resize" && argc == 5) {
            String inputPath = argv[2];
            String outputPath = argv[3];
            double factor = std::stod(argv[4]);
            Gimpsep::resizeImage(inputPath, outputPath, factor);
        } else if (option == "--resize" && argc == 6 && String(argv[2]) == "--video") {
            String inputPath = argv[3];
            String outputPath = argv[4];
            double factor = std::stod(argv[5]);
            Gimpsep::resizeVideo(inputPath, outputPath, factor);
        } else if (option == "--lighten-darken" && argc == 5) {
            String inputPath = argv[2];
            String outputPath = argv[3];
            double factor = std::stod(argv[4]);
            Gimpsep::lightenDarken(inputPath, outputPath, factor);
        } else if (option == "--lighten-darken" && argc == 6 && String(argv[2]) == "--video") {
            String inputPath = argv[3];
            String outputPath = argv[4];
            double factor = std::stod(argv[5]);
            Gimpsep::lightenDarkenVideo(inputPath, outputPath, factor);
        } else if (option == "--panorama") {
            String outputPath = argv[2];
            std::vector<String> *inputPaths = new std::vector<String>();
            for (int i = 3; i < argc; i++) {
                inputPaths->emplace_back(argv[i]);
            }
            Gimpsep::stitch(inputPaths, outputPath);
        } else if (option == "--canny" && argc == 7) {
            String inputPath = argv[2];
            String outputPath = argv[3];
            double threshold1 = std::stod(argv[4]);
            double threshold2 = std::stod(argv[5]);
            int apertureSize = std::stoi(argv[6]);
            Gimpsep::cannyEdgeDetection(inputPath, outputPath, threshold1, threshold2, apertureSize);
        } else if (option == "--canny" && argc == 8 && String(argv[2]) == "--video") {
            String inputPath = argv[3];
            String outputPath = argv[4];
            double threshold1 = std::stod(argv[5]);
            double threshold2 = std::stod(argv[6]);
            int apertureSize = std::stoi(argv[7]);
            Gimpsep::cannyEdgeDetectionVideo(inputPath, outputPath, threshold1, threshold2, apertureSize);
        } else {
            std::cout << "Could not find any option accepting the given input parameters!" << std::endl;
            return 1;
        }
    }

    return 0;
}

void help() {
    std::cout << "Usage of GIMPSEP-C-IMP:" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --dilate [--video] <input_path> <output_path> <dilate_size>: Perform dilatation" << std::endl;
    std::cout << "  --erode [--video] <input_path> <output_path> <dilate_size>: Perform erosion" << std::endl;
    std::cout << "  --resize [--video] <input_path> <output_path> <width> <height>: Resize the image" << std::endl;
    std::cout << "  --resize [--video] <input_path> <output_path> <factor>: Resize the image by factor" << std::endl;
    std::cout << "  --lighten-darken [--video] <input_path> <output_path> <factor>: Lighten or darken the image/video" << std::endl;
    std::cout << "  --panorama <output_path> [input_paths]: Create a panorama by stitching images" << std::endl;
    std::cout << "  --canny [--video] <input_path> <output_path> <threshold1> <threshold2> <aperture_size>: ";
    std::cout << "Perform Canny edge detection" << std::endl;
}
