# CS010B coursework

Independent C++ exercises retain their original assignment names and nested paths. [Original course README](README.original.md) preserves the original description and academic-use notice.

Use a C++17 compiler. From the collection root, select one folder; set an absolute output directory outside the checkout:

```bash
export COURSEWORK_BUILD_DIR="$HOME/GoalRuns/ucr-coursework-builds"
mkdir -p "$COURSEWORK_BUILD_DIR"
cd courses/cs010b/2.10
clang++ -std=c++17 *.cpp -o "$COURSEWORK_BUILD_DIR/exercise"
"$COURSEWORK_BUILD_DIR/exercise"
```

Run from that same assignment directory so relative data paths work. Do not compile all course files together. Build outputs and newly generated results belong outside this source tree. Commands below describe the preserved source; compilation does not establish correctness for every input.

| Assignment folder | Retained source / resources | Build result on Apple Clang 21 |
| --- | --- | --- |
| [10.1](10.1/) | `IntList.cpp`, `IntList.h`, `main.cpp` | Compiles |
| [10.2](10.2/) | `main.cpp` | Compiles |
| [2.10](2.10/) | `lab2part1.dat`, `lab2part1a.txt`, `main.cpp` | Compiles |
| [2.11/LAB 2 (Ex.2) - File I_O Characters](2.11/LAB%202%20%28Ex.2%29%20-%20File%20I_O%20Characters/) | `alpha.txt`, `main.cpp` | Compiles |
| [2.12/2.13/PROGRAM 1_ Calculating Coefficient Of Lift](2.12/2.13/PROGRAM%201_%20Calculating%20Coefficient%20Of%20Lift/) | `main.cpp` | Compiles |
| [2.12/LAB 2 (Ex.3)_ File I_O - CSV update](2.12/LAB%202%20%28Ex.3%29_%20File%20I_O%20-%20CSV%20update/) | `data1.csv`, `data2.csv`, `main.cpp` | Compiles |
| [2.13/PROGRAM 1_ Calculating Coefficient Of Lift](2.13/PROGRAM%201_%20Calculating%20Coefficient%20Of%20Lift/) | `main.cpp`, `tunnel1.dat`, `tunnel2.dat` | Compiles |
| [3.1](3.1/) | `main.cpp` | Compiles |
| [3.13 Prog](3.13%20Prog/) | `main 2.cpp` | Compiles |
| [4.1/LAB 4_ Classes (Distance)](4.1/LAB%204_%20Classes%20%28Distance%29/) | `Distance.cpp`, `Distance.h`, `main.cpp` | Compiles |
| [4.2](4.2/) | `ItemToPurchase.cpp`, `ItemToPurchase.h`, `ShoppingCart.cpp`, `ShoppingCart.h`, `main.cpp` | Historical failure (see below) |
| [5.1/Lab 5 (Midterm Practice)](5.1/Lab%205%20%28Midterm%20Practice%29/) | `Time.cpp`, `Time.h`, `main.cpp` | Historical failure (see below) |
| [6.1](6.1/) | `IntVector.cpp`, `IntVector.h`, `main.cpp` | Compiles |
| [6.2](6.2/) | `IntVector.cpp`, `IntVector.h`, `main.cpp` | Compiles |
| [7.10](7.10/) | `IntList.cpp`, `IntList.h`, `main.cpp` | Compiles |
| [8.00](8.00/) | `Character.cpp`, `Character.h`, `Elf.cpp`, `Elf.h`, `Warrior.cpp`, `Warrior.h`, `Wizard.cpp`, `Wizard.h`, `main.cpp` | Compiles |
| [8.1](8.1/) | `IntList.cpp`, `IntList.h`, `SortedSet.cpp`, `SortedSet.h`, `main.cpp` | Compiles |
| [9.0](9.0/) | `main.cpp` | Compiles |
| [9.2](9.2/) | `main.cpp`, `minFunc.cpp`, `minFunc.h` | Compiles |
| [9.3](9.3/) | `IntList.cpp`, `IntList.h`, `main.cpp` | Compiles |
| [misc/delete](misc/delete/) | `IntList.cpp` | Historical failure (see below) |
| [misc/delete/example](misc/delete/example/) | `main.cpp` | Compiles |
| [misc/delete/helloworld](misc/delete/helloworld/) | `main.cpp` | Compiles |

## Inputs and preserved limitations

`2.10`: enter `lab2part1.dat` (checked sum: 286). `2.11/LAB 2 (Ex.2) - File I_O Characters`: enter `alpha.txt`, then `a` (checked count: 1). `10.1`: enter `0` to run the supplied head/tail swap case (5 6 7 → 7 6 5).

`2.12/LAB 2 (Ex.3)_ File I_O - CSV update` takes input/output arguments but historically writes `dataOut.csv` in its cwd regardless of the requested output name. Run a scratch copy outside the checkout for that exercise. The two `2.12/2.13` and `2.13` lift programs are distinct retained versions. The latter takes `tunnel1.dat` or `tunnel2.dat`, expects `Yes`/`No`, and calls `exit(1)` on `No`; this is preserved.

Historical compiler failures: `4.2` has ShoppingCart definition/declaration mismatches; `5.1/Lab 5 (Midterm Practice)` references `_appm` while the field is `_ampm`; `misc/delete/IntList.cpp` has no accompanying `IntList.h` in the original tree. The `delete` directory contained actual C++ work despite its name and is retained under `misc/delete/`. Other compiled exercises have warnings or incomplete behavior; only the representative cases above were executed.

Home-directory/editor/cache paths, compiled files and empty placeholders are omitted from this current academic tree. Their exact original paths/blobs and reasons are in the root manifest; raw history remains private and uninspected for excluded paths.
