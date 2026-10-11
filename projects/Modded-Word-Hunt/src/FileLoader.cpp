#include "../include/FileLoader.h"
#include <fstream>
#include <iostream>

std::vector<std::string> FileLoader::loadWordsFromFile(const std::string& fileName) {
    std::vector<std::string> words;

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << fileName << std::endl;
        return words;
    }

    std::string word;
    while (file >> word) {
        words.push_back(word);
    }

    file.close();

    return words;
}
