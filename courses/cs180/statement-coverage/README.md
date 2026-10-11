# Statement coverage quickstart

Run `python3 print_cov.py capitalize.py input1.txt` or `python3 print_cov.py bubble_sort.py input2.txt` from this directory. Standard-library Python only. [Original README](README.original.md) retains the original explanation and examples.

The function under test executes as ordinary Python code. The tracer uses a temporary module, `sys.settrace`, and a POSIX `SIGALRM` timeout of 120 seconds; Windows support is not established. Function execution warnings can coexist with exit 0, so inspect stderr and covered line output. Set `TMPDIR` to a scratch directory and `PYTHONDONTWRITEBYTECODE=1` to keep runtime artifacts outside the checkout. Only the two included examples were exercised; exception/timeout edge cases were not newly tested.
