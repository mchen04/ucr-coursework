#ifndef DEFAULTWORDSCORER_H
#define DEFAULTWORDSCORER_H

#include "WordScorer.h"

class DefaultWordScorer : public WordScorer {
public:
    int calculatePoints(const std::string& word) const override;
};

#endif
