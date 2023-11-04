#!/bin/bash

# Dir
directory="."

# Deleting .o / .bin
find "$directory" -type f \( -name "*.o" -o -name "*.bin" \) -exec rm -f {} \;

echo "Deleting tmp file"