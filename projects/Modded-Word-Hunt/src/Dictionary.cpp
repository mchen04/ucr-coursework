#include "../include/Dictionary.h"
#include "../include/FileLoader.h"
#include <iostream>
#include <algorithm>
#include <cctype>

Dictionary::Dictionary(const std::string& validWordsFile) {
    loadValidWords(validWordsFile);
}

bool Dictionary::contains(const std::string& word) const {
    std::string transformedWord = transformWord(word);
    return validWords.count(transformedWord) > 0;
}

std::vector<std::string> Dictionary::filterValidWords(const std::vector<std::string>& words) const {
    std::vector<std::string> filteredWords;
    filteredWords.reserve(words.size());

    for (const std::string& word : words) {
        if (contains(word)) {
            filteredWords.push_back(word);
        }
    }

    std::sort(filteredWords.begin(), filteredWords.end());
    filteredWords.erase(std::unique(filteredWords.begin(), filteredWords.end()), filteredWords.end());

    return filteredWords;
}

void Dictionary::loadValidWords(const std::string& validWordsFile) {
    std::vector<std::string> words = FileLoader::loadWordsFromFile(validWordsFile);
    for (const std::string& word : words) {
        std::string transformedWord = transformWord(word);
        validWords.insert(transformedWord);
    }
}

std::string Dictionary::transformWord(const std::string& word) const {
    std::string transformedWord = word;
    std::transform(transformedWord.begin(), transformedWord.end(), transformedWord.begin(), ::tolower);
    transformedWord.erase(std::find_if(transformedWord.rbegin(), transformedWord.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), transformedWord.end());
    return transformedWord;
}
