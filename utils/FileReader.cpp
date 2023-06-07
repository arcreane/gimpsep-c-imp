#include "FileReader.h"

#include <fstream>

typedef std::string String;


String FileReader::readTextFile(const String &inputFilePath) {
    std::ifstream file(inputFilePath);
    std::string content;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << inputFilePath << std::endl;
    }

    return content;
}
