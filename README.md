# Statement Coverage Analysis Tool

This tool analyzes statement coverage for Python programs. It executes a given Python function with specified input and reports which statements were covered during execution.

## Requirements

- Python 3.6 or higher
- No external libraries required (uses Python's built-in tracing capabilities)

## Installation

1. Make the script executable:

```bash
chmod +x print_cov.py
```

## Usage

Run the tool with the following command:

```bash
./print_cov.py <program_file> <input_file>
```

Where:
- `<program_file>` is the path to a Python file containing a single function
- `<input_file>` is the path to a file containing the input for the function

The input file can contain:
- A string (with or without quotes)
- An integer
- A JSON array (for multiple arguments)

## Output Format

The output shows each line of the program with a prefix:
- `#` if the statement was not executed
- Spaces if the statement was executed

The format is:
```
<hashtag_or_spaces> <line_number> <statement>
```

## Timeout Handling

If the program has infinite loops or recursions, the tool will automatically terminate execution after 2 minutes and report the coverage based on what was executed up to that point.

## Examples

### Example 1: Capitalize Function

Create a file `capitalize.py`:
```python
def capitalize(sentence: str) -> str:
    """
    Capitalizes the first letter of a sentence or word.
    """
    from string import ascii_lowercase, ascii_uppercase

    if not sentence:
        return ""

    # Create a dictionary that maps lowercase letters to uppercase letters
    # Capitalize the first character if it's a lowercase letter
    # Concatenate the capitalized character with the rest of the string
    lower_to_upper = dict(zip(ascii_lowercase, ascii_uppercase))
    return lower_to_upper.get(sentence[0], sentence[0]) + sentence[1:]
```

Create an input file `input1.txt`:
```
"hello world"
```

Run the tool:
```bash
./print_cov.py capitalize.py input1.txt
```

### Example 2: Bubble Sort

Create a file `bubble_sort.py`:
```python
def bubble_sort_recursive(collection):
    """It is similar iterative bubble sort but recursive."""
    from typing import Any, List

    length = len(collection)
    swapped = False
    for i in range(length - 1):
        if collection[i] > collection[i + 1]:
            collection[i], collection[i + 1] = collection[i + 1], collection[i]
            swapped = True

    return collection if not swapped else bubble_sort_recursive(collection)
```

Create an input file `input2.txt`:
```
[-23, 0, 6, -4, 34]
```

Run the tool:
```bash
./print_cov.py bubble_sort.py input2.txt
```

## Known Issues

There's a minor display issue where commas may be missing in the output (e.g., between imports or function arguments). This doesn't affect the core functionality of tracking statement coverage.

## Experimental Environment

This tool was developed and tested with:
- Python 3.8
- macOS Sequoia