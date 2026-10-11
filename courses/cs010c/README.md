# CS010C coursework

Independent C++ exercises retain their original assignment names and nested paths. [Original course README](README.original.md) preserves the original description and academic-use notice.

Use a C++17 compiler. From the collection root, select one folder; set an absolute output directory outside the checkout:

```bash
export COURSEWORK_BUILD_DIR="$HOME/GoalRuns/ucr-coursework-builds"
mkdir -p "$COURSEWORK_BUILD_DIR"
cd courses/cs010c/6.6
clang++ -std=c++17 *.cpp -o "$COURSEWORK_BUILD_DIR/exercise"
"$COURSEWORK_BUILD_DIR/exercise"
```

Run from that same assignment directory so relative data paths work. Do not compile all course files together. Build outputs and newly generated results belong outside this source tree. Commands below describe the preserved source; compilation does not establish correctness for every input.

| Assignment folder | Retained source / resources | Build result on Apple Clang 21 |
| --- | --- | --- |
| [1.20](1.20/) | `Playlist.cpp`, `Playlist.h`, `main.cpp` | Compiles |
| [1.24](1.24/) | `main.cpp` | Compiles |
| [2.27](2.27/) | `IntList.cpp`, `IntList.h`, `main.cpp` | Compiles |
| [2.28](2.28/) | `main.cpp` | Compiles |
| [3.14](3.14/) | `main.cpp` | Compiles |
| [3.15](3.15/) | `WordLadder.cpp`, `WordLadder.h`, `dictionary.txt`, `main.cpp`, `output.txt` | Compiles |
| [4.12](4.12/) | `main.cpp`, `stack.h` | Historical failure (see below) |
| [4.13](4.13/) | `BSTree.cpp`, `BSTree.h`, `Node.cpp`, `Node.h`, `main.cpp`, `test_bst.h` | Compiles |
| [5.14](5.14/) | `Heap.cpp`, `Heap.h`, `PrintJob.cpp`, `PrintJob.h`, `main.cpp` | Compiles |
| [6.6](6.6/) | `arithmeticExpression.cpp`, `arithmeticExpression.h`, `height_color.dot`, `inorder_color.dot`, `main.cpp`, `simple_bst.dot` | Compiles |
| [6.8](6.8/) | `Node.cpp`, `Node.h`, `Tree.cpp`, `Tree.h`, `main.cpp` | Compiles |
| [7.9](7.9/) | `AVLTree.cpp`, `AVLTree.h`, `Node.cpp`, `Node.h`, `main.cpp` | Compiles |
| [8.11](8.11/) | `HashTable.cpp`, `HashTable.h`, `WordEntry.cpp`, `WordEntry.h`, `main.cpp`, `movieReviews.txt` | Compiles with `HashTable.cpp WordEntry.cpp` only; wildcard duplicates `main` |
| [9.7](9.7/) | `main.cpp` | Compiles |
| [9.8](9.8/) | `Jug.cpp`, `Jug.h`, `main.cpp` | Compiles |

## Inputs and preserved limitations

`6.6` prints infix/prefix/postfix trees without input. `8.11` embeds a duplicate driver in `HashTable.cpp`; use this retained standalone command from that folder:

```bash
clang++ -std=c++17 HashTable.cpp WordEntry.cpp -o "$COURSEWORK_BUILD_DIR/reviews"
"$COURSEWORK_BUILD_DIR/reviews"
```

Enter a review, then an empty line to exit. The supplied `movieReviews.txt` is required. The checked `good movie` result was 2.04262 / Somewhat Positive. `3.15` uses `dictionary.txt` and overwrites `output.txt`; run a scratch copy outside the checkout to preserve its supplied sample ladder. DOT files in `6.6` and the extensionless `Final Study/midterm_badsort` are meaningful study material and are retained. The latter is an incomplete code fragment, not a runnable assignment.

Historical failure: `4.12` refers ambiguously to the custom and standard `stack` types on the checked compiler. The wildcard `8.11` build failure is resolved by selecting the existing standalone translation units above, without editing source. Other exercises compile, but only the expression and review workflows were executed.
