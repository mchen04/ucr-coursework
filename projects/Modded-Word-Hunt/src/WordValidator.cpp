#include "../include/WordValidator.h"
#include <algorithm>

std::vector<std::string> WordValidator::filterValidWords(const std::vector<std::string>& words, const std::vector<std::string>& validWords) {
    std::vector<std::string> filteredWords;
    for (const std::string& word : words) {
        if (std::binary_search(validWords.begin(), validWords.end(), word)) {
            filteredWords.push_back(word);
        }
    }
    return filteredWords;
}
