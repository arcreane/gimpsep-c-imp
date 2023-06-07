#ifndef GIMPSEP_C_IMP_FILEREADER_H
#define GIMPSEP_C_IMP_FILEREADER_H

#include <iostream>

typedef std::string String;

class FileReader {
public:
    static String readTextFile(const String& inputFilePath);
};

#endif
