#!/bin/bash

# Directory containing the error .rt files
ERROR_DIR="scenes/eval_scenes"

# Ensure test_parsing exists and is executable
if [ ! -x "./minirt" ]; then
    echo "Error: ./minirt not found or not executable"
    exit 1
fi

for file in "$ERROR_DIR"/*.rt; do
    # Skip if no .rt files found
    [ -e "$file" ] || continue

    echo "=== Running: $(basename "$file") ==="
    
    # Run parser, capture both stdout and stderr
    ./minirt "$file" 2>&1

    echo
done
