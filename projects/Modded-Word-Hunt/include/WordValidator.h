#ifndef WORDVALIDATOR_H
#define WORDVALIDATOR_H

#include <string>
#include <vector>

class WordValidator {
public:
    static std::vector<std::string> filterValidWords(const std::vector<std::string>& words, const std::vector<std::string>& validWords);
};

#endif
