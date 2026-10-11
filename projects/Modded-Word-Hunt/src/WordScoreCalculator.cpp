#include "../include/WordScoreCalculator.h"

WordScoreCalculator::WordScoreCalculator(const WordScorer& scorer) : scorer(scorer) {}

int WordScoreCalculator::calculateTotalScore(const std::vector<std::string>& words) const {
    int totalScore = 0;

    for (const std::string& word : words) {
        int wordScore = scorer.calculatePoints(word);
        totalScore += wordScore;
    }

    return totalScore;
}
