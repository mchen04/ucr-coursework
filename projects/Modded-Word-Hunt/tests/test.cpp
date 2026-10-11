#include <gtest/gtest.h>
#include "../include/WordScoreCalculator.h"
#include "../include/WordValidator.h"
#include "../include/FileLoader.h"
#include "../include/Dictionary.h"
#include "../include/DefaultWordScorer.h"
#include "../include/Settings.h"
#include "../include/CustomWordList.h"
#include <algorithm>
#include <fstream> // Include the <fstream> header
#include <cctype>
#include <iostream>

// Mock WordScorer class for testing
class MockWordScorer : public WordScorer {
public:
    int calculatePoints(const std::string& word) const override {
        // Return a fixed score for testing purposes
        // You can customize this implementation for your specific scoring logic
        if (word == "hello")
            return 5;
        else if (word == "world")
            return 10;
        else if (word == "testing")
            return 7;
        else
            return 0;  // Default score for other words
    }
};

WordScoreCalculator::WordScoreCalculator(const WordScorer& scorer) : scorer(scorer) {}

int WordScoreCalculator::calculateTotalScore(const std::vector<std::string>& words) const {
    int totalScore = 0;

    for (const std::string& word : words) {
        int wordScore = scorer.calculatePoints(word);
        totalScore += wordScore;
    }

    return totalScore;
}

// Test case for calculating total score with an empty list of words
TEST(WordScoreCalculatorTest, CalculateTotalScoreEmptyWords) {
    // Create a mock WordScorer object for testing
    MockWordScorer mockScorer;

    // Create a WordScoreCalculator object
    WordScoreCalculator calculator(mockScorer);

    // Provide an empty vector of words
    std::vector<std::string> words;

    // Calculate the total score
    int totalScore = calculator.calculateTotalScore(words);

    // The total score should be 0 for an empty list of words
    EXPECT_EQ(totalScore, 0);
}

// Test case for calculating total score with a list of words
TEST(WordScoreCalculatorTest, CalculateTotalScoreNonEmptyWords) {
    // Create a mock WordScorer object for testing
    MockWordScorer mockScorer;

    // Create a WordScoreCalculator object
    WordScoreCalculator calculator(mockScorer);

    // Provide a vector of words
    std::vector<std::string> words = { "hello", "world", "testing" };

    // Calculate the total score
    int totalScore = calculator.calculateTotalScore(words);

    // The total score should be the sum of individual word scores
    // based on the mock scorer's scoring logic
    int expectedScore = mockScorer.calculatePoints("hello") +
                        mockScorer.calculatePoints("world") +
                        mockScorer.calculatePoints("testing");
    EXPECT_EQ(totalScore, expectedScore);
}




std::vector<std::string> WordValidator::filterValidWords(const std::vector<std::string>& words, const std::vector<std::string>& validWords) {
    std::vector<std::string> filteredWords;
    for (const std::string& word : words) {
        if (std::binary_search(validWords.begin(), validWords.end(), word)) {
            filteredWords.push_back(word);
        }
    }
    return filteredWords;
}

// Test case for filtering valid words
TEST(WordValidatorTest, FilterValidWords) {
    WordValidator validator;

    std::vector<std::string> words = { "apple", "banana", "orange", "grape" };
    std::vector<std::string> validWords = { "apple", "grape" };

    std::vector<std::string> filteredWords = validator.filterValidWords(words, validWords);

    EXPECT_EQ(filteredWords.size(), 2);
    EXPECT_EQ(filteredWords[0], "apple");
    EXPECT_EQ(filteredWords[1], "grape");
}

// Test case for filtering valid words with an empty input
TEST(WordValidatorTest, FilterValidWordsEmptyInput) {
    WordValidator validator;

    std::vector<std::string> words;
    std::vector<std::string> validWords = { "apple", "grape" };

    std::vector<std::string> filteredWords = validator.filterValidWords(words, validWords);

    EXPECT_EQ(filteredWords.size(), 0);
}

// Test case for filtering valid words with an empty valid words list
TEST(WordValidatorTest, FilterValidWordsEmptyValidWords) {
    WordValidator validator;

    std::vector<std::string> words = { "apple", "banana", "orange", "grape" };
    std::vector<std::string> validWords;

    std::vector<std::string> filteredWords = validator.filterValidWords(words, validWords);

    EXPECT_EQ(filteredWords.size(), 0);
}

// Test case for filtering valid words with no matching words
TEST(WordValidatorTest, FilterValidWordsNoMatchingWords) {
    WordValidator validator;

    std::vector<std::string> words = { "apple", "banana", "orange", "grape" };
    std::vector<std::string> validWords = { "kiwi", "melon" };

    std::vector<std::string> filteredWords = validator.filterValidWords(words, validWords);

    EXPECT_EQ(filteredWords.size(), 0);
}



std::vector<std::string> FileLoader::loadWordsFromFile(const std::string& fileName) {
    std::vector<std::string> words;

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << fileName << std::endl;
        return words;
    }

    std::string word;
    while (file >> word) {
        words.push_back(word);
    }

    file.close();

    return words;
}

TEST(FileLoaderTest, LoadWordsFromFile_ValidFile) {
    FileLoader fileLoader;
    std::string fileName = "testFile.txt";

    // Create a test file with some words
    std::ofstream outFile(fileName);
    outFile << "apple" << std::endl;
    outFile << "banana" << std::endl;
    outFile << "cherry" << std::endl;
    outFile.close();

    // Load words from the file
    std::vector<std::string> words = fileLoader.loadWordsFromFile(fileName);

    // Verify the loaded words
    ASSERT_EQ(words.size(), 3);
    EXPECT_EQ(words[0], "apple");
    EXPECT_EQ(words[1], "banana");
    EXPECT_EQ(words[2], "cherry");
}

TEST(FileLoaderTest, LoadWordsFromFile_InvalidFile) {
    FileLoader fileLoader;
    std::string fileName = "nonexistent_file.txt";

    // Load words from a nonexistent file
    std::vector<std::string> words = fileLoader.loadWordsFromFile(fileName);

    // Verify that no words are loaded
    EXPECT_TRUE(words.empty());
}

TEST(FileLoaderTest, LoadWordsFromFile_EmptyFile) {
    FileLoader fileLoader;
    std::string fileName = "testFile.txt";

    // Create an empty test file
    std::ofstream outFile(fileName);
    outFile.close();

    // Load words from the file
    std::vector<std::string> words = fileLoader.loadWordsFromFile(fileName);

    // Verify that no words are loaded
    EXPECT_TRUE(words.empty());
}

TEST(FileLoaderTest, LoadWordsFromFile_SingleWordPerLine) {
    FileLoader fileLoader;
    std::string fileName = "testFile.txt";

    // Create a test file with single words on each line
    std::ofstream outFile(fileName);
    outFile << "apple" << std::endl;
    outFile << "banana" << std::endl;
    outFile << "cherry" << std::endl;
    outFile.close();

    // Load words from the file
    std::vector<std::string> words = fileLoader.loadWordsFromFile(fileName);

    // Verify the loaded words
    ASSERT_EQ(words.size(), 3);
    EXPECT_EQ(words[0], "apple");
    EXPECT_EQ(words[1], "banana");
    EXPECT_EQ(words[2], "cherry");
}

TEST(FileLoaderTest, LoadWordsFromFile_FileWithWhitespace) {
    FileLoader fileLoader;
    std::string fileName = "testFile.txt";

    // Create a test file with words and additional whitespace
    std::ofstream outFile(fileName);
    outFile << "apple" << std::endl;
    outFile << "    " << std::endl; // Empty line with whitespace
    outFile << "banana" << std::endl;
    outFile << "  cherry  " << std::endl; // Words with leading/trailing whitespace
    outFile.close();

    // Load words from the file
    std::vector<std::string> words = fileLoader.loadWordsFromFile(fileName);

    // Verify the loaded words
    ASSERT_EQ(words.size(), 3);
    EXPECT_EQ(words[0], "apple");
    EXPECT_EQ(words[1], "banana");
    EXPECT_EQ(words[2], "cherry");
}




// Tests for the Settings class
TEST(SettingsTest, SoundEnabledDefault) {
    Settings settings;
    EXPECT_FALSE(settings.isSoundEnabled());
}

TEST(SettingsTest, SetSoundEnabled) {
    Settings settings;
    settings.setSoundEnabled(true);
    EXPECT_TRUE(settings.isSoundEnabled());
}

TEST(SettingsTest, EffectsEnabledDefault) {
    Settings settings;
    EXPECT_FALSE(settings.areEffectsEnabled());
}

TEST(SettingsTest, SetEffectsEnabled) {
    Settings settings;
    settings.setEffectsEnabled(true);
    EXPECT_TRUE(settings.areEffectsEnabled());
}
// Test case for scoreMultiplierEnabled
TEST(SettingsTest, ScoreMultiplierEnabled_DefaultValue) {
    Settings settings;
    EXPECT_FALSE(settings.isScoreMultiplierEnabled());
}

TEST(SettingsTest, SetScoreMultiplierEnabled) {
    Settings settings;

    settings.setScoreMultiplierEnabled(true);
    EXPECT_TRUE(settings.isScoreMultiplierEnabled());

    settings.setScoreMultiplierEnabled(false);
    EXPECT_FALSE(settings.isScoreMultiplierEnabled());
}

// Test case for hintsEnabled
TEST(SettingsTest, HintsEnabled_DefaultValue) {
    Settings settings;
    EXPECT_FALSE(settings.areHintsEnabled());
}

TEST(SettingsTest, SetHintsEnabled) {
    Settings settings;

    settings.setHintsEnabled(true);
    EXPECT_TRUE(settings.areHintsEnabled());

    settings.setHintsEnabled(false);
    EXPECT_FALSE(settings.areHintsEnabled());
}

// Test case for powerupsEnabled
TEST(SettingsTest, PowerupsEnabled_DefaultValue) {
    Settings settings;
    EXPECT_FALSE(settings.arePowerupsEnabled());
}

TEST(SettingsTest, SetPowerupsEnabled) {
    Settings settings;

    settings.setPowerupsEnabled(true);
    EXPECT_TRUE(settings.arePowerupsEnabled());

    settings.setPowerupsEnabled(false);
    EXPECT_FALSE(settings.arePowerupsEnabled());
}

// Test case for dimensions
TEST(SettingsTest, GetDimensions_DefaultValue) {
    Settings settings;
    EXPECT_EQ(settings.getDimensions(), "4");
}

TEST(SettingsTest, SetDimensions) {
    Settings settings;

    settings.setDimensions("5");
    EXPECT_EQ(settings.getDimensions(), "5");

    settings.setDimensions("6");
    EXPECT_EQ(settings.getDimensions(), "6");
}

// Test case for soundPercent
TEST(SettingsTest, GetSoundPercent_DefaultValue) {
    Settings settings;
    EXPECT_EQ(settings.getSoundPercent(), 50);
}

TEST(SettingsTest, SetSoundPercent) {
    Settings settings;

    settings.setSoundPercent(70);
    EXPECT_EQ(settings.getSoundPercent(), 70);

    settings.setSoundPercent(80);
    EXPECT_EQ(settings.getSoundPercent(), 80);
}

// Test case for wordLimit
TEST(SettingsTest, GetWordLimit_DefaultValue) {
    Settings settings;
    EXPECT_EQ(settings.getWordLimit(), "17");
}

TEST(SettingsTest, SetWordLimit) {
    Settings settings;

    settings.setWordLimit("20");
    EXPECT_EQ(settings.getWordLimit(), "20");

    settings.setWordLimit("25");
    EXPECT_EQ(settings.getWordLimit(), "25");
}

// Test case for time
TEST(SettingsTest, GetTime_DefaultValue) {
    Settings settings;
    EXPECT_EQ(settings.getTime(), "80");
}

TEST(SettingsTest, SetTime) {
    Settings settings;

    settings.setTime("60");
    EXPECT_EQ(settings.getTime(), "60");

    settings.setTime("90");
    EXPECT_EQ(settings.getTime(), "90");
}

// Tests for the CustomWordList class
TEST(CustomWordListTest, AddCustomWord) {
    CustomWordList customWordList;
    customWordList.addCustomWord("apple");
    customWordList.addCustomWord("banana");
    EXPECT_EQ(customWordList.getCustomWord(0), "apple");
    EXPECT_EQ(customWordList.getCustomWord(1), "banana");
}

TEST(CustomWordListTest, GetCustomWordOutOfBounds) {
    CustomWordList customWordList;
    EXPECT_THROW(customWordList.getCustomWord(0), std::out_of_range);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
