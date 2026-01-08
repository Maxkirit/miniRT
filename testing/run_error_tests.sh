#!/bin/bash

# Directory containing the error .rt files
ERROR_DIR="error_scenes_exhaustive"

# Ensure test_parsing exists and is executable
if [ ! -x "./test_parsing" ]; then
    echo "Error: ./test_parsing not found or not executable"
    exit 1
fi

for file in "$ERROR_DIR"/*.rt; do
    # Skip if no .rt files found
    [ -e "$file" ] || continue

    echo "=== Running: $(basename "$file") ==="
    
    # Run parser, capture both stdout and stderr
    ./test_parsing "$file" 2>&1

    echo
done
