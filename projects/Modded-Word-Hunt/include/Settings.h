#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include "ISettings.h"
#include "CustomWordList.h"

class Settings : public ISettings {
public:
    Settings();

    // Destructor doesn't need to deallocate memory for the vector anymore

    // Implement the methods from the ISettings interface
    bool isSoundEnabled() const override;
    void setSoundEnabled(bool enabled) override;

    bool areEffectsEnabled() const override;
    void setEffectsEnabled(bool enabled) override;

    bool isScoreMultiplierEnabled() const override;
    void setScoreMultiplierEnabled(bool enabled) override;

    bool areHintsEnabled() const override;
    void setHintsEnabled(bool enabled) override;

    bool arePowerupsEnabled() const override;
    void setPowerupsEnabled(bool enabled) override;

    std::string getDimensions() const override;
    void setDimensions(const std::string& dimensions) override;

    int getSoundPercent() const override;
    void setSoundPercent(int percent) override;

    std::string getWordLimit() const override;
    void setWordLimit(const std::string& limit) override;

    std::string getTime() const override;
    void setTime(const std::string& time) override;

    void addToCustomWordList(const std::string& word);
    void clearList();

private:
    bool soundEnabled;
    bool effectsEnabled;
    bool scoreMultiplierEnabled;
    bool hintsEnabled;
    bool powerupsEnabled;
    std::string dimensions;
    int soundPercent;
    std::string wordLimit;
    std::string time;
    CustomWordList customWordList;
};

#endif /* SETTINGS_H */
