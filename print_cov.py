#!/usr/bin/env python3
import sys
import os
import ast
import json
import importlib.util
import signal
import traceback
import tempfile
import inspect
from typing import Any, List, Dict, Tuple, Set

def load_program(program_path: str) -> Tuple[str, str]:
    """
    Load a Python program from a file.
    Returns the program code and the function name.
    """
    with open(program_path, 'r') as f:
        program_code = f.read()
    
    # Parse the program to get the function name
    tree = ast.parse(program_code)
    function_name = None
    for node in ast.walk(tree):
        if isinstance(node, ast.FunctionDef):
            function_name = node.name
            break
    
    if not function_name:
        raise ValueError("No function found in the program")
    
    return program_code, function_name

def load_input(input_path: str) -> Any:
    """
    Load input from a file. The input can be an integer, a string, or an array.
    """
    with open(input_path, 'r') as f:
        input_str = f.read().strip()
    
    # Try to parse as JSON (for arrays or complex structures)
    try:
        return json.loads(input_str)
    except json.JSONDecodeError:
        # If not JSON, try to parse as int
        try:
            return int(input_str)
        except ValueError:
            # If not int, return as string
            return input_str

def timeout_handler(signum, frame):
    """Handler for timeout signal"""
    raise TimeoutError("Program execution timed out (2 minutes)")

def run_with_trace(program_code: str, function_name: str, input_data: Any) -> Dict[int, bool]:
    """
    Run the program with the given input and track statement coverage using sys.settrace.
    Returns a dictionary mapping line numbers to coverage status.
    """
    # Create a temporary file for the program
    fd, temp_file_path = tempfile.mkstemp(suffix='.py')
    os.close(fd)
    
    with open(temp_file_path, 'w') as f:
        f.write(program_code)
    
    # Import the module
    module_name = os.path.basename(temp_file_path)[:-3]  # Remove .py extension
    spec = importlib.util.spec_from_file_location(module_name, temp_file_path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    
    # Get the function
    func = getattr(module, function_name)
    
    # Set up line tracing
    executed_lines = set()
    
    def trace_calls(frame, event, arg):
        if event != 'call':
            return
        return trace_lines
    
    def trace_lines(frame, event, arg):
        if event != 'line':
            return
        
        # Get the filename from the frame
        filename = frame.f_code.co_filename
        
        # Only track lines from our temporary file
        if filename == temp_file_path:
            lineno = frame.f_lineno
            executed_lines.add(lineno)
        
        return trace_lines
    
    # Set timeout (2 minutes)
    signal.signal(signal.SIGALRM, timeout_handler)
    signal.alarm(120)  # 120 seconds = 2 minutes
    
    try:
        # Enable tracing
        sys.settrace(trace_calls)
        
        # Call the function with the input
        # Check if the function expects a single argument
        sig = inspect.signature(func)
        params = list(sig.parameters.values())
        
        # If the function has only one parameter and input is a list,
        # pass the list as a single argument
        if len(params) == 1 and isinstance(input_data, list):
            func(input_data)
        # Otherwise, if input is a list, unpack it
        elif isinstance(input_data, list):
            func(*input_data)
        # If input is not a list, pass it directly
        else:
            func(input_data)
            
    except TimeoutError:
        print("Warning: Program execution timed out (2 minutes limit)", file=sys.stderr)
    except Exception as e:
        print(f"Warning: Program execution failed: {e}", file=sys.stderr)
        traceback.print_exc(file=sys.stderr)
    finally:
        # Disable tracing
        sys.settrace(None)
        
        # Cancel the alarm
        signal.alarm(0)
        
        # Clean up
        if os.path.exists(temp_file_path):
            os.remove(temp_file_path)
        
        # Create coverage data
        coverage_data = {}
        for line in range(1, len(program_code.split('\n')) + 1):
            coverage_data[line] = line in executed_lines
        
        return coverage_data

def print_coverage(program_code: str, coverage_data: Dict[int, bool]) -> None:
    """
    Print the coverage information in the required format.
    """
    lines = program_code.split('\n')
    for i, line in enumerate(lines, 1):
        # Check if the line is covered
        is_covered = coverage_data.get(i, False)
        
        # Print the coverage information
        prefix = "  " if is_covered else "# "
        print(f"{prefix} {i:4d}  {line}")

def main():
    if len(sys.argv) != 3:
        print("Usage: ./print_cov.py <program_file> <input_file>")
        sys.exit(1)
    
    program_path = sys.argv[1]
    input_path = sys.argv[2]
    
    # Load the program and input
    program_code, function_name = load_program(program_path)
    input_data = load_input(input_path)
    
    # Run the program with coverage tracking
    coverage_data = run_with_trace(program_code, function_name, input_data)
    
    # Print the coverage information
    print_coverage(program_code, coverage_data)

if __name__ == "__main__":
    main()