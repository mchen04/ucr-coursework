#include "../include/DefaultWordScorer.h"

int DefaultWordScorer::calculatePoints(const std::string& word) const {
    int wordLength = word.length();

    if (wordLength >= 3) {
        if (wordLength == 3) {
            return 100;
        } else if (wordLength == 4) {
            return 400;
        } else if (wordLength == 5) {
            return 800;
        } else if (wordLength >= 6) {
            return (400 * wordLength) - 1000;
        }
    }

    return 0;
}
