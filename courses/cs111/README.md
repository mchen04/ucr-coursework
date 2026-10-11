# CS111 · Discrete structures

[Homework 2](hw2/) retains `cs111_hw2.cpp` and the [original course README](hw2/README.md). This is a toy RSA arithmetic/decoding exercise; no real credential or key file is included.

```bash
export COURSEWORK_BUILD_DIR="$HOME/GoalRuns/ucr-coursework-builds"
mkdir -p "$COURSEWORK_BUILD_DIR"
cd courses/cs111/hw2
clang++ -std=c++17 cs111_hw2.cpp -o "$COURSEWORK_BUILD_DIR/cs111-hw2"
printf '7 77 3
47 41 59
' | "$COURSEWORK_BUILD_DIR/cs111-hw2"
```

Input is exponent `e`, modulus `n`, message length, then that many ciphertext integers. The supplied synthetic example decodes `5 6 31` to `AB ` and prints factors `7 11`, phi `60`, inverse `43`. An exponent of 1 produces `Public key is not valid!` with exit 0; read output when judging results. Original integer-overflow/input limits and the exercise's letter mapping remain unchanged. The two old compiled executables and Finder metadata are omitted; exact history is retained.
