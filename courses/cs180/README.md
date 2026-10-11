# CS180 · Statement coverage

[Statement coverage project](statement-coverage/README.md): independent Python tracing assignment with supplied programs and input files. Use that project directory as cwd. Standard library only; no environment/package installation required.

```bash
cd courses/cs180/statement-coverage
python3 print_cov.py capitalize.py input1.txt
python3 print_cov.py bubble_sort.py input2.txt
```

Both examples ran on Python 3.12.13 with executed/unexecuted line output and no execution warnings. Read stderr as well as the exit code: the original tracer catches function exceptions/timeouts and may still return coverage with exit 0. No behavior was changed. Historical bytecode is omitted from the current tree.
