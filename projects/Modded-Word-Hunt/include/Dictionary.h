#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <unordered_set>
#include <vector>

class Dictionary {
private:
    std::unordered_set<std::string> validWords;

public:
    Dictionary(const std::string& validWordsFile);

    bool contains(const std::string& word) const;

    std::vector<std::string> filterValidWords(const std::vector<std::string>& words) const;

private:
    void loadValidWords(const std::string& validWordsFile);
    std::string transformWord(const std::string& word) const;
};

#endif
