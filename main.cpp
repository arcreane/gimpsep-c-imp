#include <iostream>
#include <vector>


int main(int argc, char **argv) {
    if (argc <= 2) {
        std::cout << "Usage: " << argv[0] << "[options]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  --dilate-erode <input_path> <output_path>: Perform dilatation and erosion" << std::endl;
        std::cout << "  --resize <input_path> <output_path> <width> <height>: Resize the image" << std::endl;
        std::cout << "  --resize <input_path> <output_path> <factor>: Resize the image by factor" << std::endl;
        std::cout << "  --lighten-darken <input_path> <output_path> <factor>: Lighten or darken the image" << std::endl;
        std::cout << "  --panorama <output_path> [<input_path>]: Create a panorama by stitching images" << std::endl;
        std::cout << "  --canny <input_path> <output_path> <threshold1> <threshold2> <kernel_size>: ";
        std::cout << "Perform Canny edge detection" << std::endl;

        return 1;
    } else {
        std::string option = argv[1];
        std::cout << argc << std::endl;

        if (option == "--dilate-erode" && argc == 5) {
            std::string inputPath = argv[2];
            std::string outputPath = argv[3];
            int erosionSize = std::stoi(argv[4]);
            // dilateErode(inputPath, outputPath, erosionSize);
        } else if (option == "--resize" && argc == 6) {
            std::string inputPath = argv[2];
            std::string outputPath = argv[3];
            int width = std::stoi(argv[4]);
            int height = std::stoi(argv[5]);
            // resizeImage(inputPath, outputPath, width, height);
        } else if (option == "--resize" && argc == 5) {
            std::string inputPath = argv[2];
            std::string outputPath = argv[3];
            double factor = std::stod(argv[4]);
            // resizeImage(inputPath, outputPath, factor);
        } else if (option == "--lighten-darken" && argc == 5) {
            std::string inputPath = argv[2];
            std::string outputPath = argv[3];
            double factor = std::stod(argv[4]);
            // lightenDarken(inputPath, outputPath, value);
        } else if (option == "--panorama") {
            std::string outputPath = argv[2];
            std::vector<std::string> inputPaths;
            for (int i = 2; i < argc; i++) {
                inputPaths.emplace_back(argv[i]);
            }
            // panorama(inputPaths, outputPath);
        } else if (option == "--canny" && argc == 7) {
            std::string inputPath = argv[2];
            std::string outputPath = argv[3];
            double threshold1 = std::stod(argv[4]);
            double threshold2 = std::stod(argv[5]);
            int kernelSize = std::stoi(argv[6]);
            // cannyEdgeDetection(inputPath, outputPath, threshold1, threshold2, kernelSize);
        } else {
            std::cout << "Could not find any option accepting the given input parameters!" << std::endl;
            return 1;
        }
    }

    return 0;
}
