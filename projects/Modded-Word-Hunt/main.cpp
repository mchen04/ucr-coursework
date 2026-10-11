#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include <iostream>
#include <cctype>
#include <fstream>
#include <algorithm>
#include "include/ButtonCustom.h"
#include "include/ButtonRenderer.h"
#include "include/Dictionary.h"
#include "include/Board.h"
#include "include/Piece.h"
#include "include/Text.h"
#include "include/TextRenderer.h"
#include "include/Settings.h"
#include "include/WordScorer.h"
#include "include/DefaultWordScorer.h"
#include "include/WordScoreCalculator.h"
#include "include/BoardRenderer.h"

using namespace std;

void settingScreen(sf::RenderWindow& window, Settings &userSettings) ;
void mainMenu(sf::RenderWindow& window, Settings &userSettings) ;
void gameScreen(sf::RenderWindow& window, Settings& userSettings ) ;
void scoreScreen(sf::RenderWindow& window, Settings& userSettings, Board& board ) ;
vector<string> filterValidWords(const vector<string>& words, const string& validWordsFile) ;
int calculateTotalScore(const vector<string>& words) ;

// Function to get the mouse position relative to the window
sf::Vector2f getMousePosition(const sf::RenderWindow& window) {
    sf::Vector2i intVector = sf::Mouse::getPosition(window);
    sf::Vector2f floatVector(static_cast<float>(intVector.x), static_cast<float>(intVector.y));
    return floatVector;
}

// Function to render the main menu
void mainMenu(sf::RenderWindow& window, Settings& userSettings) {
    // Clear the window
    window.clear(sf::Color::White);

    // Load the gif texture
    sf::Texture gifTexture;
    if (!gifTexture.loadFromFile("main_menu.gif")) {
        return;
    }

    // Create and configure the gif sprite
    sf::Sprite gifSprite(gifTexture);
    gifSprite.setScale(
        static_cast<float>(window.getSize().x) / gifSprite.getLocalBounds().width,
        static_cast<float>(window.getSize().y) / gifSprite.getLocalBounds().height
    );

    // Load the font
    sf::Font font;
    if (!font.loadFromFile("Poppins-Black.ttf")) {
        return;
    }

    // Calculate relative positions and sizes based on window size
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);
    sf::Vector2f titlePosition(windowWidth * 0.100f, windowHeight * 0.033f);
    sf::Vector2f playButtonPosition(windowWidth * 0.3667f, windowHeight * 0.5333f);
    sf::Vector2f settingsButtonPosition(windowWidth * 0.3667f, windowHeight * 0.7f);

    // Create the title text
    Text title(font, "Modified Word Hunt", static_cast<unsigned int>(windowHeight * 0.08f), sf::Color::White, sf::Color::Black, 6.0f, titlePosition);

    // Create the text renderer for the title
    TextRenderer titleRenderer(title);

    // Create the buttons
    ButtonCustom playButton(
        playButtonPosition.x,
        playButtonPosition.y,
        windowWidth * 0.15f,
        windowHeight * 0.0667f,
        font,
        "Play",
        sf::Color::Black,
        sf::Color::White,
        sf::Color(70, 70, 70, 200)
    );
    ButtonCustom settingsButton(
        settingsButtonPosition.x,
        settingsButtonPosition.y,
        windowWidth * 0.27f,
        windowHeight * 0.0667f,
        font,
        "Settings",
        sf::Color::Black,
        sf::Color::White,
        sf::Color(70, 70, 70, 200)
    );

    // Create the button renderer for the play button
    ButtonRenderer playButtonRenderer(playButton);

    // Create the button renderer for the settings button
    ButtonRenderer settingsButtonRenderer(settingsButton);

    // Game loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Update button states
            playButton.update(getMousePosition(window));
            settingsButton.update(getMousePosition(window));

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if play button is clicked
                    if (playButton.isPressed()) {
                        // Do something when "Play" button is clicked
                        gameScreen(window, userSettings);
                        break;
                    }
                    // Check if settings button is clicked
                    if (settingsButton.isPressed()) {
                        settingScreen(window, userSettings);
                    }
                }
            }
        }

        window.draw(gifSprite);

        // Render the title text
        titleRenderer.render(window);

        // Render the play button
        playButtonRenderer.render(window);

        // Render the settings button
        settingsButtonRenderer.render(window);

        window.display();
    }
}


void settingScreen(sf::RenderWindow& window, Settings &userSettings) {
    window.clear(sf::Color::White);

    // Load font for the text
    sf::Font font;
    if (!font.loadFromFile("Poppins-Black.ttf")) {
        return;
    }

    // Calculate relative positions based on window size
    sf::Vector2f windowSize(window.getSize().x, window.getSize().y);
    sf::Vector2f titlePosition = sf::Vector2f(windowSize.x * 0.34f, windowSize.y * 0.04f);

    sf::Vector2f dimensionPosition = sf::Vector2f(windowSize.x * 0.05f, windowSize.y * 0.22f);
    sf::Vector2f soundEffectPosition = sf::Vector2f(windowSize.x * 0.05f, windowSize.y * 0.366f); 
    sf::Vector2f soundDimension = sf::Vector2f(windowSize.x * 0.05f, windowSize.y * 0.516f);
    sf::Vector2f wordDimension = sf::Vector2f(windowSize.x * 0.05f, windowSize.y * 0.665f);
    sf::Vector2f scoreMultiplierPosition = sf::Vector2f(windowSize.x * 0.05f, windowSize.y * 0.817f);

    sf::Vector2f hintPosition = sf::Vector2f(windowSize.x * 0.67f, windowSize.y * 0.22f);
    sf::Vector2f timerPosition = sf::Vector2f(windowSize.x * 0.577f, windowSize.y * 0.366f);
    sf::Vector2f powerupPosition = sf::Vector2f(windowSize.x * 0.6f, windowSize.y * 0.516f);
    sf::Vector2f wordListPosition = sf::Vector2f(windowSize.x * 0.61f, windowSize.y * 0.665f);
    sf::Vector2f backPosition = sf::Vector2f(windowSize.x * 0.675f, windowSize.y * 0.817f);

    Text titleText(font, "Settings", 120, sf::Color::White, sf::Color::Black, 6.0f, titlePosition);
    Text dimensionText(font, "Dimensions", 40, sf::Color::White, sf::Color::Black, 6.0f, dimensionPosition);
    Text soundEffectText(font, "Sound Effects", 40, sf::Color::White, sf::Color::Black, 6.0f, soundEffectPosition);
    Text soundText(font, "Sound %", 40, sf::Color::White, sf::Color::Black, 6.0f, soundDimension);
    Text wordText(font, "Word Limit", 40, sf::Color::White, sf::Color::Black, 6.0f, wordDimension);
    Text scoreMultiplierText(font, "Score Multiplier", 40, sf::Color::White, sf::Color::Black, 6.0f, scoreMultiplierPosition);
    Text hintText(font, "Hints", 40, sf::Color::White, sf::Color::Black, 6.0f, hintPosition);
    Text timerText(font, "Timer Amount", 40, sf::Color::White, sf::Color::Black, 6.0f, timerPosition);
    Text powerupText(font, "Powerups", 40, sf::Color::White, sf::Color::Black, 6.0f, powerupPosition);
    Text wordListText(font, "Word List", 40, sf::Color::White, sf::Color::Black, 6.0f, wordListPosition);
    Text backText(font, "Back", 40, sf::Color::White, sf::Color::Black, 6.0f, backPosition);

    TextRenderer titleTextRenderer(titleText);
    TextRenderer dimensionTextRenderer(dimensionText);
    TextRenderer soundEffectTextRenderer(soundEffectText);
    TextRenderer soundTextRenderer(soundText);
    TextRenderer wordTextRenderer(wordText);
    TextRenderer scoreMultiplierTextRenderer(scoreMultiplierText);
    TextRenderer hintTextRenderer(hintText);
    TextRenderer timerTextRenderer(timerText);
    TextRenderer powerupTextRenderer(powerupText);
    TextRenderer wordListTextRenderer(wordListText);
    TextRenderer backTextRenderer(backText);

    // Initialize button labels based on user settings
    sf::Color soundButtonColor = userSettings.areEffectsEnabled() ? sf::Color::Green : sf::Color::Red;
    sf::Color scoreMultiplierButtonColor = userSettings.isScoreMultiplierEnabled() ? sf::Color::Green : sf::Color::Red;
    sf::Color hintButtonColor = userSettings.areHintsEnabled() ? sf::Color::Green : sf::Color::Red;
    sf::Color powerupButtonColor = userSettings.arePowerupsEnabled() ? sf::Color::Green : sf::Color::Red;

    // Initialize button labels based on user settings
    string soundButtonText = userSettings.areEffectsEnabled() ? "On" : "Off";
    string scoreMultiplierButtonText = userSettings.isScoreMultiplierEnabled() ? "On" : "Off";
    string hintButtonText = userSettings.areHintsEnabled() ? "On" : "Off";
    string powerupButtonText = userSettings.arePowerupsEnabled() ? "On" : "Off";

    // Create buttons using the Button class
    ButtonCustom hintButton(1140, 290, 325, 100, font, hintButtonText, hintButtonColor, hintButtonColor, hintButtonColor);
    ButtonCustom soundeffectButton(400, 510, 325, 100, font, soundButtonText, soundButtonColor , soundButtonColor, soundButtonColor);
    ButtonCustom scoreMultiplierButton(430, 1185, 325, 100, font, scoreMultiplierButtonText, scoreMultiplierButtonColor, scoreMultiplierButtonColor, scoreMultiplierButtonColor);
    ButtonCustom powerupButton(1140, 740, 325, 100, font, powerupButtonText, powerupButtonColor, powerupButtonColor, powerupButtonColor);
    ButtonCustom backButton(1140, 1185, 325, 100, font, "<-", sf::Color::White, sf::Color::White, sf::Color(70, 70, 70, 200));

    ButtonRenderer hintButtonRenderer(hintButton);
    ButtonRenderer soundeffectButtonRenderer(soundeffectButton);
    ButtonRenderer scoreMultiplierButtonRenderer(scoreMultiplierButton);
    ButtonRenderer powerupButtonRenderer(powerupButton);
    ButtonRenderer backButtonRenderer(backButton);

    //Create slider
    sf::RectangleShape soundSlider(sf::Vector2f(200, 20));
    soundSlider.setFillColor(sf::Color::White);
    soundSlider.setPosition(windowSize.x * 0.20, windowSize.y * 0.52f);

    // Slider handle properties
    sf::RectangleShape soundHandle(sf::Vector2f(20, 40));
    soundHandle.setFillColor(sf::Color::Red);
    soundHandle.setPosition(soundSlider.getPosition().x - soundHandle.getSize().x * 0.5f, soundSlider.getPosition().y - soundHandle.getSize().y * 0.5f);

    sf::Text valueText("", font, 30);
    valueText.setFillColor(sf::Color::White);
    valueText.setPosition(windowSize.x * 0.255, windowSize.y * 0.538f);

    float sliderMin = soundSlider.getPosition().x;
    float sliderMax = soundSlider.getPosition().x + soundSlider.getSize().x;
    float handleWidth = soundHandle.getSize().x;
    bool isDragging = false;

    int sliderValue = userSettings.getSoundPercent();
    soundHandle.setPosition(sliderMin + sliderValue * (sliderMax - sliderMin) / 100.0f - handleWidth * 0.5f, soundHandle.getPosition().y);
    
    //Create text input
    sf::Text timeInputText("", font, 40);
    timeInputText.setFillColor(sf::Color::Black);
    timeInputText.setString(userSettings.getTime());
    timeInputText.setPosition(windowSize.x * 0.80f, windowSize.y * 0.366f);

    sf::Text dimensionInputText("", font, 40);
    dimensionInputText.setFillColor(sf::Color::Black);
    dimensionInputText.setString(userSettings.getDimensions());
    dimensionInputText.setPosition(windowSize.x * 0.225f, windowSize.y * 0.222f);
    
    sf::Text limitInputText("", font, 40);
    limitInputText.setFillColor(sf::Color::Black);
    limitInputText.setString(userSettings.getWordLimit());
    limitInputText.setPosition(windowSize.x * 0.219, windowSize.y * 0.6672f);

    sf::Text customInputText("", font, 40);
    customInputText.setFillColor(sf::Color::Black);
    customInputText.setPosition(windowSize.x * 0.758f, windowSize.y * 0.6672f);

    sf::RectangleShape timerBox;
    timerBox.setSize(sf::Vector2f(250.0f, 45.0f));
    timerBox.setFillColor(sf::Color::White);
    timerBox.setOutlineColor(sf::Color::Black);
    timerBox.setOutlineThickness(1.0f);
    timerBox.setPosition(windowSize.x * 0.80f, windowSize.y * 0.366f);

    sf::RectangleShape dimensionBox;
    dimensionBox.setSize(sf::Vector2f(250.0f, 45.0f));
    dimensionBox.setFillColor(sf::Color::White);
    dimensionBox.setOutlineColor(sf::Color::Black);
    dimensionBox.setOutlineThickness(1.0f);
    dimensionBox.setPosition(windowSize.x * 0.225f, windowSize.y * 0.222f);

    sf::RectangleShape wordLimitBox;
    wordLimitBox.setSize(sf::Vector2f(250.0f, 45.0f));
    wordLimitBox.setFillColor(sf::Color::White);
    wordLimitBox.setOutlineColor(sf::Color::Black);
    wordLimitBox.setOutlineThickness(1.0f);
    wordLimitBox.setPosition(windowSize.x * 0.219f, windowSize.y * 0.6672f);

    sf::RectangleShape customBox;
    customBox.setSize(sf::Vector2f(250.0f, 45.0f));
    customBox.setFillColor(sf::Color::White);
    customBox.setOutlineColor(sf::Color::Black);
    customBox.setOutlineThickness(1.0f);
    customBox.setPosition(windowSize.x * 0.758f, windowSize.y * 0.6672f);

    sf::RectangleShape timeCursor;
    timeCursor.setSize(sf::Vector2f(2.0f, 40.0f));
    timeCursor.setFillColor(sf::Color::Black);

    sf::RectangleShape dimensionCursor;
    dimensionCursor.setSize(sf::Vector2f(2.0f, 40.0f));
    dimensionCursor.setFillColor(sf::Color::Black);

    sf::RectangleShape limitCursor;
    limitCursor.setSize(sf::Vector2f(2.0f, 40.0f));
    limitCursor.setFillColor(sf::Color::Black);

    sf::RectangleShape customCursor;
    customCursor.setSize(sf::Vector2f(2.0f, 40.0f));
    customCursor.setFillColor(sf::Color::Black);

    string timeInputString = userSettings.getTime();
    string dimensionInputString = userSettings.getDimensions();
    string limitInputString = userSettings.getWordLimit();
    string customInputString = "";

    bool showTimeCursor = false;
    bool showDimensionCursor = false;
    bool showLimitCursor = false;
    bool showCustomCursor = false;

    sf::Clock timeCursorTimer;
    const sf::Time timeCursorInterval = sf::seconds(0.5f);

    sf::Clock dimensionCursorTimer;
    const sf::Time dimensionCursorInterval = sf::seconds(0.5f);

    sf::Clock limitCursorTimer;
    const sf::Time limitCursorInterval = sf::seconds(0.5f);

    sf::Clock customCursorTimer;
    const sf::Time customCursorInterval = sf::seconds(0.5f);

    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Update button states
            backButton.update(getMousePosition(window));
            soundeffectButton.update(getMousePosition(window));
            scoreMultiplierButton.update(getMousePosition(window));
            hintButton.update(getMousePosition(window));
            powerupButton.update(getMousePosition(window));

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (soundHandle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isDragging = true;
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if settings button is clicked
                    if (backButton.isPressed()) {
                        mainMenu(window, userSettings);
                    }
                    if (soundeffectButton.isPressed()) {
                        if (userSettings.areEffectsEnabled())
                        {
                            userSettings.setEffectsEnabled(false) ;
                        }
                        else 
                        {
                            userSettings.setEffectsEnabled(true) ;
                        }

                        if (userSettings.areEffectsEnabled())
                        {
                            soundeffectButton.setText("On") ;
                            soundeffectButton.setIdleColor(sf::Color::Green) ;
                            soundeffectButton.setHoverColor(sf::Color::Green) ;
                        }
                        else
                        {
                            soundeffectButton.setText("Off") ;
                            soundeffectButton.setIdleColor(sf::Color::Red) ;
                            soundeffectButton.setHoverColor(sf::Color::Red) ;
                        }
                    }
                    if (scoreMultiplierButton.isPressed()) {
                        if (userSettings.isScoreMultiplierEnabled())
                        {
                            userSettings.setScoreMultiplierEnabled(false) ;
                        }
                        else 
                        {
                            userSettings.setScoreMultiplierEnabled(true) ;
                        }

                        if (userSettings.isScoreMultiplierEnabled())
                        {
                            scoreMultiplierButton.setText("On") ;
                            scoreMultiplierButton.setIdleColor(sf::Color::Green) ;
                            scoreMultiplierButton.setHoverColor(sf::Color::Green) ;
                        }
                        else
                        {
                            scoreMultiplierButton.setText("Off") ;
                            scoreMultiplierButton.setIdleColor(sf::Color::Red) ;
                            scoreMultiplierButton.setHoverColor(sf::Color::Red) ;
                        }
                    }
                    if (hintButton.isPressed()) {
                        if (userSettings.areHintsEnabled())
                        {
                            userSettings.setHintsEnabled(false) ;
                        }
                        else 
                        {
                            userSettings.setHintsEnabled(true) ;
                        }

                        if (userSettings.areHintsEnabled())
                        {
                            hintButton.setText("On") ;
                            hintButton.setIdleColor(sf::Color::Green) ;
                            hintButton.setHoverColor(sf::Color::Green) ;
                        }
                        else
                        {
                            hintButton.setText("Off") ;
                            hintButton.setIdleColor(sf::Color::Red) ;
                            hintButton.setHoverColor(sf::Color::Red) ;
                        }
                    }
                    if (powerupButton.isPressed()) {
                        if (userSettings.arePowerupsEnabled())
                        {
                            userSettings.setPowerupsEnabled(false) ;
                        }
                        else 
                        {
                            userSettings.setPowerupsEnabled(true) ;
                        }

                        if (userSettings.arePowerupsEnabled())
                        {
                            powerupButton.setText("On") ;
                            powerupButton.setIdleColor(sf::Color::Green) ;
                            powerupButton.setHoverColor(sf::Color::Green) ;
                        }
                        else
                        {
                            powerupButton.setText("Off") ;
                            powerupButton.setIdleColor(sf::Color::Red) ;
                            powerupButton.setHoverColor(sf::Color::Red) ;
                        }
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                isDragging = false;
            }
            else if (event.type == sf::Event::MouseMoved && isDragging) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                float mouseX = static_cast<float>(mousePos.x);
                // Clamp the mouse position to the slider bounds
                if (mouseX < sliderMin) {
                    mouseX = sliderMin;
                } else if (mouseX > sliderMax) {
                    mouseX = sliderMax;
                }
                // Calculate the new slider value based on the mouse position
                sliderValue = static_cast<int>((mouseX - sliderMin) / (sliderMax - sliderMin) * 100.0f);
                userSettings.setSoundPercent(sliderValue);
                // Move the slider handle based on the new value
                soundHandle.setPosition(mouseX - handleWidth * 0.5f, soundHandle.getPosition().y);
                // Update the value text
                ostringstream oss;
                oss << sliderValue;
                valueText.setString(oss.str());
            }
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (timerBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if(event.type == sf::Event::MouseButtonPressed) {
                    showTimeCursor = true;
                    showDimensionCursor = false;
                    showLimitCursor = false;
                    showCustomCursor = false;
                }
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode >= 48 && event.text.unicode <= 57) {// Check if the entered character is a number
                        timeInputString += static_cast<char>(event.text.unicode);
                        timeInputText.setString(timeInputString);
                        userSettings.setTime(timeInputString);
                    }
                    else if (event.text.unicode == 8 && !timeInputText.getString().isEmpty()) {// Check if the entered character is the backspace key
                        timeInputString.pop_back();
                        timeInputText.setString(timeInputString);
                        userSettings.setTime(timeInputString);
                    }
                }
            }
            else if (dimensionBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if(event.type == sf::Event::MouseButtonPressed) {
                    showTimeCursor = false;
                    showDimensionCursor = true;
                    showLimitCursor = false;
                    showCustomCursor = false;
                }
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode >= 48 && event.text.unicode <= 57) {// Check if the entered character is a number
                        dimensionInputString += static_cast<char>(event.text.unicode);
                        dimensionInputText.setString(dimensionInputString);
                        userSettings.setDimensions(dimensionInputString);
                    }
                    else if (event.text.unicode == 8 && !dimensionInputText.getString().isEmpty()) {// Check if the entered character is the backspace key
                        dimensionInputString.pop_back();
                        dimensionInputText.setString(dimensionInputString);
                        userSettings.setDimensions(dimensionInputString);
                    }
                }
            }
            else if (wordLimitBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if(event.type == sf::Event::MouseButtonPressed) {
                    showTimeCursor = false;
                    showDimensionCursor = false;
                    showLimitCursor = true;
                    showCustomCursor = false;
                }
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode >= 48 && event.text.unicode <= 57) {// Check if the entered character is a number
                        limitInputString += static_cast<char>(event.text.unicode);
                        limitInputText.setString(limitInputString);
                        userSettings.setWordLimit(limitInputString);
                    }
                    else if (event.text.unicode == 8 && !limitInputText.getString().isEmpty()) {// Check if the entered character is the backspace key
                        limitInputString.pop_back();
                        limitInputText.setString(limitInputString);
                        userSettings.setWordLimit(limitInputString);
                    }
                }
            }
            else if (customBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if(event.type == sf::Event::MouseButtonPressed) {
                    showTimeCursor = false;
                    showDimensionCursor = false;
                    showLimitCursor = false;
                    showCustomCursor = true;
                }
                if (event.type == sf::Event::TextEntered) {
                    if ((event.text.unicode >= 65 && event.text.unicode <= 90) || (event.text.unicode >= 97 && event.text.unicode <= 122)) {// Check if the entered character is a letter
                        customInputString += static_cast<char>(event.text.unicode);
                        customInputText.setString(customInputString);
                    }
                    if (event.text.unicode == 8 && !customInputText.getString().isEmpty()) {// Check if the entered character is the backspace key
                        customInputString.pop_back();
                        customInputText.setString(customInputString);
                    }
                    if( event.text.unicode ==  10) {
                        cout<<"Enter"<<endl;
                        userSettings.addToCustomWordList(customInputString);
                        // cout<<userSettings.getCustomWordList(0)<<endl;
                        customInputString = "";
                    }
                    if(customInputString=="clear") {
                        userSettings.clearList();
                        customInputString = "";
                    }
                }
            }
        }

        window.clear();

        soundeffectButtonRenderer.render(window);
        scoreMultiplierButtonRenderer.render(window);
        hintButtonRenderer.render(window);
        powerupButtonRenderer.render(window);
        backButtonRenderer.render(window);

        window.draw(soundSlider);
        window.draw(soundHandle);
        window.draw(valueText);

        titleTextRenderer.render(window);
        dimensionTextRenderer.render(window);
        soundEffectTextRenderer.render(window);
        soundTextRenderer.render(window);
        wordTextRenderer.render(window);
        scoreMultiplierTextRenderer.render(window);
        hintTextRenderer.render(window);
        timerTextRenderer.render(window);
        powerupTextRenderer.render(window);
        wordListTextRenderer.render(window);
        backTextRenderer.render(window);
        
        // Cursor blinking
        if (timeCursorTimer.getElapsedTime() >= timeCursorInterval){
            showTimeCursor = !showTimeCursor;
            timeCursorTimer.restart();
        }
        if (dimensionCursorTimer.getElapsedTime() >= dimensionCursorInterval){
            showDimensionCursor = !showDimensionCursor;
            dimensionCursorTimer.restart();
        }
        if (limitCursorTimer.getElapsedTime() >= limitCursorInterval){
            showLimitCursor = !showLimitCursor;
            limitCursorTimer.restart();
        }
        if (customCursorTimer.getElapsedTime() >= customCursorInterval){
            showCustomCursor = !showCustomCursor;
            customCursorTimer.restart();
        }

        // Update cursor position
        timeCursor.setPosition(timerBox.getPosition().x + timeInputText.getLocalBounds().width + 2, timerBox.getPosition().y + 3);
        dimensionCursor.setPosition(dimensionBox.getPosition().x + dimensionInputText.getLocalBounds().width + 2, dimensionBox.getPosition().y + 3);
        limitCursor.setPosition(wordLimitBox.getPosition().x + limitInputText.getLocalBounds().width + 2, wordLimitBox.getPosition().y + 3);
        customCursor.setPosition(customBox.getPosition().x + customInputText.getLocalBounds().width + 2, customBox.getPosition().y + 3);

        window.draw(timerBox);
        window.draw(timeInputText);

        window.draw(dimensionBox);
        window.draw(dimensionInputText);

        window.draw(wordLimitBox);
        window.draw(limitInputText);

        window.draw(customBox);
        window.draw(customInputText);

        // Draw cursor if it's visible
        if (showTimeCursor && !showLimitCursor && !showDimensionCursor && !showCustomCursor)
            window.draw(timeCursor);
        if (!showTimeCursor && showLimitCursor && !showDimensionCursor && !showCustomCursor)
            window.draw(limitCursor);
        if (!showTimeCursor && !showLimitCursor && showDimensionCursor && !showCustomCursor)
            window.draw(dimensionCursor);
        if (!showTimeCursor && !showLimitCursor && !showDimensionCursor && showCustomCursor)
            window.draw(customCursor);
        
        // Display the window
        window.display();
    }
}

void gameScreen(sf::RenderWindow& window, Settings& userSettings)
{
    window.clear(sf::Color::White);

    // Calculate relative positions and sizes based on window size
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);
    sf::Vector2f titlePosition(windowWidth * 0.100f, windowHeight * 0.033f);

    string boardDimensions = userSettings.getDimensions();
    unsigned int boardDimensionInt = stoul(boardDimensions);
    Board board(boardDimensionInt);
    BoardRenderer boardRend(board);

    board.initializeRandomLetters();

    // Game loop
    sf::Clock timerClock;
    sf::Time timeLimit = sf::seconds(std::stoi(userSettings.getTime())); // Convert string to int
    bool isTimeUp = false;

    while (window.isOpen() && !isTimeUp)
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
            board.update(getMousePosition(window), isMousePressed);
        }

        // Update the timer
        sf::Time elapsedTime = timerClock.getElapsedTime();
        if (elapsedTime >= timeLimit)
        {
            isTimeUp = true;
        }

        window.clear();

        //board.render(window); // Implement the render function for your Board class
        boardRend.render(window);
        
        window.display();
    }

    // Go to the ScoreScreen or perform any other necessary actions
    scoreScreen(window, userSettings, board);  // Call the ScoreScreen function or replace with your implementation
}




void scoreScreen(sf::RenderWindow& window, Settings& userSettings, Board& board) {
    // Clear the window
    window.clear(sf::Color::White);

    // Load the font
    sf::Font font;
    if (!font.loadFromFile("Poppins-Black.ttf")) {
        return;
    }

    Dictionary dictionary("Dictionary.txt");
    std::vector<std::string> wordVector = dictionary.filterValidWords(board.getWordList());


    sf::RectangleShape textBox(sf::Vector2f(400.f, 920.f));
    textBox.setFillColor(sf::Color::White);
    textBox.setOutlineThickness(2.f);
    textBox.setOutlineColor(sf::Color::Black);
    textBox.setPosition(200.f, 325.f);

    Text text(font, "", 60, sf::Color::Black, sf::Color::Transparent, 0.0f, sf::Vector2f(220.f, 335.f));
    TextRenderer textRenderer(text);

    sf::RectangleShape slider(sf::Vector2f(10.f, 10.f));
    slider.setFillColor(sf::Color::Black);
    slider.setOutlineThickness(1.f);
    slider.setOutlineColor(sf::Color::Black);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(93);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(855.f, 470.f);

    WordScorer* defaultWordScorer = new DefaultWordScorer();  // Create an instance of DefaultWordScorer
    WordScoreCalculator wordScoreCalculator(*defaultWordScorer);  // Pass the DefaultWordScorer instance to WordScoreCalculator constructor
    int score = wordScoreCalculator.calculateTotalScore(wordVector);

    delete defaultWordScorer;

    string scoreString = to_string(score);
    scoreText.setString(scoreString);

    sf::FloatRect textBounds = scoreText.getLocalBounds();

    float padding = 10.0f; // Set your desired padding value here

    float boxWidth = textBounds.width + (2 * padding);
    float boxHeight = textBounds.height + (2 * padding);

    // Set the size and position of the scoreBox
    sf::RectangleShape scoreBox(sf::Vector2f(boxWidth, boxHeight));
    scoreBox.setFillColor(sf::Color::White);
    scoreBox.setOutlineThickness(2.f);
    scoreBox.setOutlineColor(sf::Color::Black);
    scoreBox.setPosition(scoreText.getPosition().x - padding, scoreText.getPosition().y - padding);

    // Adjust the y-coordinate of the scoreText position to center it vertically within the score box
    float textOffsetY = (boxHeight - textBounds.height) / 2.f;
    scoreText.setPosition(scoreBox.getPosition().x + padding, scoreBox.getPosition().y - textOffsetY);

    unsigned int visibleLines = 10;
    unsigned int scrollOffset = 0;

    stringstream ss;
    for (unsigned int i = 0; i < visibleLines && i < wordVector.size(); ++i) {
        ss << wordVector[i] << "\n";
    }
    text.setString(ss.str());

    bool isDraggingSlider = false;
    sf::Vector2f sliderDragOffset;

    // Calculate relative positions and sizes based on window size
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);
    sf::Vector2f titlePosition(windowWidth * 0.1f, windowHeight * 0.05f);

    // Create the title text
    Text titleText(font, "Score Screen", static_cast<int>(windowHeight * 0.08f), sf::Color::White, sf::Color::Black, 6.0f, titlePosition);
    TextRenderer titleTextRenderer(titleText);

    // Game loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    int delta = event.mouseWheelScroll.delta;
                    if (delta > 0 && scrollOffset > 0) {
                        scrollOffset--;
                    }
                    else if (delta < 0 && scrollOffset + visibleLines < wordVector.size()) {
                        scrollOffset++;
                    }

                    stringstream ss;
                    for (unsigned int i = scrollOffset; i < scrollOffset + visibleLines && i < wordVector.size(); ++i) {
                        ss << wordVector[i] << "\n";
                    }
                    text.setString(ss.str());
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    if (slider.getGlobalBounds().contains(mousePos)) {
                        isDraggingSlider = true;
                        sliderDragOffset = mousePos - slider.getPosition();
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDraggingSlider = false;
                }
            }
            else if (event.type == sf::Event::MouseMoved) {
                if (isDraggingSlider) {
                    sf::Vector2f mousePos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                    float sliderY = mousePos.y - sliderDragOffset.y;
                    float maxSliderY = textBox.getPosition().y + textBox.getSize().y - slider.getSize().y;
                    float minSliderY = textBox.getPosition().y;
                    sliderY = max(minSliderY, min(maxSliderY, sliderY));
                    slider.setPosition(slider.getPosition().x, sliderY);

                    float contentHeight = text.getLocalBounds().height;
                    float textBoxHeight = textBox.getSize().y;
                    float sliderPosition = (slider.getPosition().y - textBox.getPosition().y) / (textBoxHeight - slider.getSize().y);
                    scrollOffset = static_cast<unsigned int>(sliderPosition * (wordVector.size() - visibleLines));

                    stringstream ss;
                    for (unsigned int i = scrollOffset; i < scrollOffset + visibleLines && i < wordVector.size(); ++i) {
                        ss << wordVector[i] << "\n";
                    }
                    text.setString(ss.str());
                }
            }
        }

        float contentHeight = text.getLocalBounds().height;
        float textBoxHeight = textBox.getSize().y;
        float fixedSliderHeight = 100.f; // Set your desired fixed slider height here
        float sliderPosition = (scrollOffset / static_cast<float>(wordVector.size() - visibleLines)) * (textBoxHeight - fixedSliderHeight);

        slider.setSize(sf::Vector2f(20.f, fixedSliderHeight));
        slider.setPosition(textBox.getPosition().x + textBox.getSize().x - slider.getSize().x - 5.f, textBox.getPosition().y + sliderPosition);

        window.clear(sf::Color::White);
        titleTextRenderer.render(window);
        window.draw(textBox);
        textRenderer.render(window);
        window.draw(slider);
        window.draw(scoreBox);
        window.draw(scoreText);
        window.display();
    }
}

int main() {
    //promptAndCalculatePoints();
    sf::RenderWindow window(sf::VideoMode(1500, 1500), "Modified Word Hunt");
    Settings userSettings;
    mainMenu(window, userSettings);
    return EXIT_SUCCESS;
}