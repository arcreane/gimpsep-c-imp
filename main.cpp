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
            // dilate(inputPath, outputPath, dilationSize);
        } else if (option == "--erode" && argc == 5) {
            String inputPath = argv[2];
            String outputPath = argv[3];
            int erosionSize = std::stoi(argv[4]);
            // erode(inputPath, outputPath, erosionSize);
        } else if (option == "--resize" && argc == 6) {
            String inputPath = argv[2];
            String outputPath = argv[3];
            int width = std::stoi(argv[4]);
            int height = std::stoi(argv[5]);
            // resizeImage(inputPath, outputPath, width, height);
        } else if (option == "--resize" && argc == 5) {
            String inputPath = argv[2];
            String outputPath = argv[3];
            double factor = std::stod(argv[4]);
            // resizeImage(inputPath, outputPath, factor);
        } else if (option == "--lighten-darken" && argc == 5) {
            String inputPath = argv[2];
            String outputPath = argv[3];
            double factor = std::stod(argv[4]);
            // lightenDarken(inputPath, outputPath, factor);
        } else if (option == "--stitch") {
            String outputPath = argv[2];
            std::vector<String> inputPaths;
            for (int i = 2; i < argc; i++) {
                inputPaths.emplace_back(argv[i]);
            }
            // stitch(inputPaths, outputPath);
        } else if (option == "--canny" && argc == 7) {
            String inputPath = argv[2];
            String outputPath = argv[3];
            double threshold1 = std::stod(argv[4]);
            double threshold2 = std::stod(argv[5]);
            int apertureSize = std::stoi(argv[6]);
            Gimpsep::cannyEdgeDetection(inputPath, outputPath, threshold1, threshold2, apertureSize);
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
    std::cout << "  --dilate <input_path> <output_path>: Perform dilatation" << std::endl;
    std::cout << "  --erode <input_path> <output_path>: Perform erosion" << std::endl;
    std::cout << "  --resize <input_path> <output_path> <width> <height>: Resize the image" << std::endl;
    std::cout << "  --resize <input_path> <output_path> <factor>: Resize the image by factor" << std::endl;
    std::cout << "  --lighten-darken <input_path> <output_path> <factor>: Lighten or darken the image" << std::endl;
    std::cout << "  --panorama <output_path> [input_paths]: Create a panorama by stitching images" << std::endl;
    std::cout << "  --canny <input_path> <output_path> <threshold1> <threshold2> <aperture_size>: ";
    std::cout << "Perform Canny edge detection" << std::endl;
}
