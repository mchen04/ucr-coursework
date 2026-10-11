#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include <vector>

class FileLoader {
public:
    static std::vector<std::string> loadWordsFromFile(const std::string& fileName);
};

#endif
