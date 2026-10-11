#ifndef WORDSCORER_H
#define WORDSCORER_H

#include <string>

class WordScorer {
public:
    virtual int calculatePoints(const std::string& word) const = 0;
    virtual ~WordScorer() {}
};

#endif
