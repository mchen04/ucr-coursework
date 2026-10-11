# CS061 · Machine organization and LC-3

[Original course README](README.original.md). Files are grouped by lab/assignment; original filenames and assembly contents are unchanged. Each assembly source is independent.

| Group | Retained files |
| --- | --- |
| assignments/assignment-01 | [assignment1.asm](assignments/assignment-01/assignment1.asm) |
| assignments/assignment-02 | [assignment2.asm](assignments/assignment-02/assignment2.asm) |
| assignments/assignment-03 | [assignment3.asm](assignments/assignment-03/assignment3.asm) |
| assignments/assignment-04 | [assignment4.asm](assignments/assignment-04/assignment4.asm) |
| assignments/assignment-05 | [assignment5.asm](assignments/assignment-05/assignment5.asm) |
| discussions/discussion-01 | [Discussion1_Practice](discussions/discussion-01/Discussion1_Practice) |
| labs/lab-01 | [Lab1_ex0.asm](labs/lab-01/Lab1_ex0.asm), [Lab1_ex1.asm](labs/lab-01/Lab1_ex1.asm) |
| labs/lab-02 | [Lab2_ex1.asm](labs/lab-02/Lab2_ex1.asm), [Lab2_ex2.asm](labs/lab-02/Lab2_ex2.asm), [Lab2_ex3.asm](labs/lab-02/Lab2_ex3.asm), [Lab2_ex4.asm](labs/lab-02/Lab2_ex4.asm) |
| labs/lab-03 | [Lab3_ex0.asm](labs/lab-03/Lab3_ex0.asm), [Lab3_ex1.asm](labs/lab-03/Lab3_ex1.asm), [Lab3_ex3.asm](labs/lab-03/Lab3_ex3.asm), [Lab3_ex4.asm](labs/lab-03/Lab3_ex4.asm) |
| labs/lab-04 | [Lab4_ex1.asm](labs/lab-04/Lab4_ex1.asm), [Lab4_ex2.asm](labs/lab-04/Lab4_ex2.asm), [Lab4_ex3.asm](labs/lab-04/Lab4_ex3.asm), [Lab4_ex4.asm](labs/lab-04/Lab4_ex4.asm) |
| labs/lab-05 | [Lab5_ex1.asm](labs/lab-05/Lab5_ex1.asm), [Lab5_ex2.asm](labs/lab-05/Lab5_ex2.asm), [Lab5_ex3.asm](labs/lab-05/Lab5_ex3.asm) |
| labs/lab-06 | [Lab6_ex1.asm](labs/lab-06/Lab6_ex1.asm), [Lab6_ex2.asm](labs/lab-06/Lab6_ex2.asm), [Lab6_ex3.asm](labs/lab-06/Lab6_ex3.asm) |
| labs/lab-07 | [Lab7_ex1.asm](labs/lab-07/Lab7_ex1.asm), [Lab7_ex2.asm](labs/lab-07/Lab7_ex2.asm), [Lab7_ex3.asm](labs/lab-07/Lab7_ex3.asm) |
| labs/lab-08 | [Lab8_ex1.asm](labs/lab-08/Lab8_ex1.asm), [Lab8_ex2.asm](labs/lab-08/Lab8_ex2.asm) |

## Assemble and simulate

Use an LC-3 assembler and simulator, such as [LC3 Tools](https://github.com/haplesshero13/lc3tools). Keep `.obj`/`.sym` outputs outside the checkout; this assembler writes them beside its input:

```bash
export COURSEWORK_BUILD_DIR="$HOME/GoalRuns/ucr-coursework-builds/lc3"
mkdir -p "$COURSEWORK_BUILD_DIR"
cd courses/cs061/assignments/assignment-01
cp assignment1.asm "$COURSEWORK_BUILD_DIR/assignment1.asm"
lc3as "$COURSEWORK_BUILD_DIR/assignment1.asm"
lc3sim "$COURSEWORK_BUILD_DIR/assignment1.obj"
```

All 31 source files assembled in the consolidation checks. Assignment 1 ran to the instruction before HALT with R3=`x0048` (72). Interactive input/traps and every later lab were not fully simulated. `Discussion1_Practice` is assembly text despite having no extension; copy it to a scratch filename ending in `.asm` when assembling.

The external LC3 Tools revision `31455c63b1e81ece0716a7a639ff244b55bcd4bc` needed an ARM64 tool compatibility fix in the evidence-only tool clone: its 32-bit `long` sign-extension mask rejected valid high addresses and its own OS source. The corrected mask was `~0xFFFFL`; the tool was compiled natively with `-std=gnu89 -fcommon`. No course source or algorithm was changed. A working course-provided LC-3 environment may already avoid this issue.
