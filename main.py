#!/usr/bin/env python3
import os
import subprocess
import sys
from pathlib import Path

def find_bin_files(task_folders):
    """Find all .bin files in the specified task folders."""
    bin_files = []
    for folder in task_folders:
        if os.path.isdir(folder):
            for file in Path(folder).glob("*.bin"):
                bin_files.append(file)
        else:
            print(f"Warning: Folder '{folder}' not found, skipping...")
    return bin_files

def run_executable(executable, bin_file):
    """Run main.out with the given .bin file as argument."""
    try:
        result = subprocess.run(
            [executable, str(bin_file)],
            capture_output=True,
            text=True,
            check=True
        )
        return True, result.stdout
    except subprocess.CalledProcessError as e:
        return False, f"Error: {e.stderr}"
    except FileNotFoundError:
        return False, f"Error: Executable '{executable}' not found"

def compare_files(file1, file2):
    """Compare two files using binary comparison and return True if they match."""
    try:
        with open(file1, 'rb') as f1, open(file2, 'rb') as f2:
            content1 = f1.read()
            content2 = f2.read()
            return content1 == content2
    except FileNotFoundError as e:
        return None  # File doesn't exist
    except Exception as e:
        print(f"Error comparing files: {e}")
        return None

def main():
    # Configuration
    executable = "./main.exe"
    task_folders = ["task1", "task2", "task3", "task4"]
    
    # Check if executable exists
    if not os.path.isfile(executable):
        print(f"Error: Executable '{executable}' not found!")
        sys.exit(1)
    
    # Find all .bin files
    print("Searching for .bin files...")
    bin_files = find_bin_files(task_folders)
    
    if not bin_files:
        print("No .bin files found!")
        sys.exit(1)
    
    print(f"Found {len(bin_files)} .bin files\n")
    
    # Results tracking
    passed = 0
    failed = 0
    errors = 0
    
    # Process each .bin file
    for bin_file in bin_files:
        base_name = bin_file.stem  # filename without extension
        folder = bin_file.parent
        
        print(f"Processing: {bin_file}")
        
        # Run the executable
        success, output = run_executable(executable, bin_file)
        
        if not success:
            print(f"  ❌ Failed to run: {output}\n")
            errors += 1
            continue
        
        # Determine output and expected files
        answer_file = folder / f"{base_name}Answer.res"
        expected_file = folder / f"{base_name}.res"
        
        # Check if output file was created
        if not answer_file.is_file():
            print(f"  ❌ Output file '{answer_file}' was not created\n")
            errors += 1
            continue
        
        # Check if expected file exists
        if not expected_file.is_file():
            print(f"  ⚠️  Expected file '{expected_file}' not found\n")
            errors += 1
            continue
        
        # Compare files
        match = compare_files(answer_file, expected_file)
        
        if match is None:
            print(f"  ❌ Error comparing files\n")
            errors += 1
        elif match:
            print(f"  ✅ PASSED - Output matches expected result\n")
            passed += 1
        else:
            print(f"  ❌ FAILED - Output does not match expected result\n")
            failed += 1
    
    # Summary
    print("=" * 50)
    print("SUMMARY")
    print("=" * 50)
    print(f"Total tests: {len(bin_files)}")
    print(f"Passed:      {passed}")
    print(f"Failed:      {failed}")
    print(f"Errors:      {errors}")
    print("=" * 50)
    
    # Exit with appropriate code
    if failed > 0 or errors > 0:
        sys.exit(1)
    else:
        sys.exit(0)

if __name__ == "__main__":
    main()