#ifndef ISETTINGS_H
#define ISETTINGS_H

#include <string>

class ISettings {
public:
    virtual ~ISettings() = default;

    virtual bool isSoundEnabled() const = 0;
    virtual void setSoundEnabled(bool enabled) = 0;

    virtual bool areEffectsEnabled() const = 0;
    virtual void setEffectsEnabled(bool enabled) = 0;

    virtual bool isScoreMultiplierEnabled() const = 0;
    virtual void setScoreMultiplierEnabled(bool enabled) = 0;

    virtual bool areHintsEnabled() const = 0;
    virtual void setHintsEnabled(bool enabled) = 0;

    virtual bool arePowerupsEnabled() const = 0;
    virtual void setPowerupsEnabled(bool enabled) = 0;

    virtual std::string getDimensions() const = 0;
    virtual void setDimensions(const std::string& dimensions) = 0;

    virtual int getSoundPercent() const = 0;
    virtual void setSoundPercent(int percent) = 0;

    virtual std::string getWordLimit() const = 0;
    virtual void setWordLimit(const std::string& limit) = 0;

    virtual std::string getTime() const = 0;
    virtual void setTime(const std::string& time) = 0;
};

#endif /* ISETTINGS_H */
