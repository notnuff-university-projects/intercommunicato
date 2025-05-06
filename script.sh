#!/bin/bash

# Define output file
output_file="project_structure.txt"

# Define files and directories to exclude
exclude_files=("src/lab2.drawio" "lab2.drawio")
exclude_dirs=(".git" ".idea" "cmake-build-debug")

# Clear the output file if it exists
> "$output_file"

# Function to check if a file should be excluded
should_exclude_file() {
    for exclude in "${exclude_files[@]}"; do
        if [[ "$1" == *"$exclude" ]]; then
            return 0
        fi
    done
    return 1
}

# Function to check if a directory should be excluded
should_exclude_dir() {
    for exclude in "${exclude_dirs[@]}"; do
        if [[ "$1" == *"$exclude" ]]; then
            return 0
        fi
    done
    return 1
}

# Function to process files
process_files() {
    for file in "$1"/*; do
        if [ -d "$file" ]; then
            # Check if the directory is in the exclude list
            if should_exclude_dir "$file"; then
                continue
            fi
            # If it's a directory, call process_files recursively
            process_files "$file"
        elif [[ "$file" == *.cpp || "$file" == *.h || "$file" == *CMakeLists.txt ]]; then
            # Check if the file is in the exclude list
            if should_exclude_file "$file"; then
                continue
            fi
            # If it's a file with a matching extension and not excluded, add directory structure and content
            echo "**===== $file =====**" >> "$output_file"
            cat "$file" >> "$output_file"
            echo -e "\n\n" >> "$output_file"
        fi
    done
}

# Start processing from the current directory
process_files "."

echo "Filtered .cpp, .h, and CMakeLists.txt files have been saved to $output_file."
