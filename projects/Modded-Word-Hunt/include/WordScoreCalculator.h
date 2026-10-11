#ifndef WORDSCORECALCULATOR_H
#define WORDSCORECALCULATOR_H

#include <string>
#include <vector>
#include "WordScorer.h"

class WordScoreCalculator {
private:
    const WordScorer& scorer;

public:
    WordScoreCalculator(const WordScorer& scorer);

    int calculateTotalScore(const std::vector<std::string>& words) const;
};

#endif
