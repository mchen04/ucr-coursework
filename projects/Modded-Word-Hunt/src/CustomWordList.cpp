#include "../include/CustomWordList.h"

void CustomWordList::clearList() {
    customWords.clear();
}

std::string CustomWordList::getCustomWord(int index) const {
    if (index >= 0 && index < customWords.size()) {
        return customWords[index];
    }
    else {
        throw std::out_of_range("Index out of bounds");
    }
}

void CustomWordList::addCustomWord(const std::string& word) {
    customWords.push_back(word);
}
