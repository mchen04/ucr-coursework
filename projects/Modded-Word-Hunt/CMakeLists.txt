cmake_minimum_required(VERSION 3.16)
project(WordHunt CXX)

find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics)

ADD_SUBDIRECTORY(googletest)

add_executable(WordHunt 
    main.cpp 
    src/ButtonCustom.cpp 
    src/ButtonRenderer.cpp
    src/Board.cpp
    src/Piece.cpp
    src/Dictionary.cpp
    src/Settings.cpp
    src/WordValidator.cpp
    src/WordScoreCalculator.cpp
    src/DefaultWordScorer.cpp
    src/CustomWordList.cpp
    src/FileLoader.cpp
    src/TextRenderer.cpp
    src/Text.cpp
    src/Slider.cpp
    src/BoardRenderer.cpp
)

add_executable(test
    tests/test.cpp
    src/CustomWordList.cpp
    src/Settings.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)

target_link_libraries(WordHunt PRIVATE sfml-graphics)
target_compile_features(WordHunt PRIVATE cxx_std_17)