#include "../include/Settings.h"

Settings::Settings()
    : soundEnabled(false),
      effectsEnabled(false),
      scoreMultiplierEnabled(false),
      hintsEnabled(false),
      powerupsEnabled(false),
      dimensions("4"),
      soundPercent(50),
      wordLimit("17"),
      time("80")
{
}

bool Settings::isSoundEnabled() const {
    return soundEnabled;
}

void Settings::setSoundEnabled(bool enabled) {
    soundEnabled = enabled;
}

bool Settings::areEffectsEnabled() const {
    return effectsEnabled;
}

void Settings::setEffectsEnabled(bool enabled) {
    effectsEnabled = enabled;
}

bool Settings::isScoreMultiplierEnabled() const {
    return scoreMultiplierEnabled;
}

void Settings::setScoreMultiplierEnabled(bool enabled) {
    scoreMultiplierEnabled = enabled;
}

bool Settings::areHintsEnabled() const {
    return hintsEnabled;
}

void Settings::setHintsEnabled(bool enabled) {
    hintsEnabled = enabled;
}

bool Settings::arePowerupsEnabled() const {
    return powerupsEnabled;
}

void Settings::setPowerupsEnabled(bool enabled) {
    powerupsEnabled = enabled;
}

std::string Settings::getDimensions() const {
    return dimensions;
}

void Settings::setDimensions(const std::string& dimensions) {
    this->dimensions = dimensions;
}

int Settings::getSoundPercent() const {
    return soundPercent;
}

void Settings::setSoundPercent(int percent) {
    soundPercent = percent;
}

std::string Settings::getWordLimit() const {
    return wordLimit;
}

void Settings::setWordLimit(const std::string& limit) {
    wordLimit = limit;
}

std::string Settings::getTime() const {
    return time;
}

void Settings::setTime(const std::string& time) {
    this->time = time;
}

void Settings::addToCustomWordList(const std::string& word) {
    customWordList.addCustomWord(word);
}

void Settings::clearList() {
    customWordList.clearList();
}