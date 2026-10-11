# Modded Word Hunt · CS100 classroom project

Private owned fork of [`cs100/final-project-fsong009-mchen356-ayen019-sshak015`](https://github.com/cs100/final-project-fsong009-mchen356-ayen019-sshak015), created through GitHub Classroom. Authors: Alex Yen, Freddy Song, Michael Chen and Sazen Shakya. [Original README](README.original.md) retains their links, project description, original screenshots and historical results. Keep team/classroom work private; no relicensing is implied.

All source, dictionary, font, sound, images, diagrams and the pinned GoogleTest gitlink are retained. Asset filenames/case and the original cwd remain significant. Modern navigation to the retained diagrams: [navigation](Images/Navigation_Diagram.jpeg), [layout](Images/SCREEN_LAYOUT.png), [UML](Images/UML_DIAGRAM.png), [SOLID](Images/SOLID_diagram2.png), [test screenshot](Images/Tests.png).

## Original GUI build

From the collection root, initialize the existing pinned dependency; the new root `.gitmodules` maps its relocated path:

```bash
git submodule update --init projects/Modded-Word-Hunt/googletest
export COURSEWORK_BUILD_DIR="$HOME/GoalRuns/ucr-coursework-builds/word-hunt"
mkdir -p "$COURSEWORK_BUILD_DIR"
cd projects/Modded-Word-Hunt
cmake -S . -B "$COURSEWORK_BUILD_DIR/cmake"
cmake --build "$COURSEWORK_BUILD_DIR/cmake"
"$COURSEWORK_BUILD_DIR/cmake/WordHunt"
```

Prerequisites: C++17 compiler, CMake, **SFML 2.x** (original requests 2.5.1), and the retained GoogleTest revision `334704df263b480a3e9e7441ed3292a5e30a37ec`. Supply `-DSFML_DIR=<directory-with-SFMLConfig.cmake>` if it is outside CMake's search path. SFML 3 compatibility is not claimed.

On the checked Mac, original CMake configuration stops at missing SFML, so the graphical game, graphics/audio/assets, memory-leak claims and GUI interactions remain unverified. The original CMake names `src/Piece.cpp` while Git tracks `src/piece.cpp`; this will also need consideration on case-sensitive filesystems. The game's rendering source has further dependencies/assumptions; no unrelated source fix was made merely to revive it.

## Existing tests without graphics

After initializing the pinned GoogleTest dependency, compile the original test file directly from this directory:

```bash
clang++ -std=c++17 -Igoogletest/googletest/include -Igoogletest/googletest   tests/test.cpp src/Settings.cpp src/CustomWordList.cpp   googletest/googletest/src/gtest-all.cc -o "$COURSEWORK_BUILD_DIR/test"
(cd "$COURSEWORK_BUILD_DIR" && ./test)
```

All 31 supplied tests from five suites pass with that pinned dependency. Run in the output directory because the tests create `testFile.txt`. These original tests embed some stand-in method definitions; passing them does not prove the GUI or every production translation unit. No new tests or game behavior changes were introduced. Preserve the original media/dictionary attribution limits: the source does not establish a blanket redistribution license for those resources.
