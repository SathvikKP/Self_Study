#!/bin/bash
echo "Compiling..."
echo "--------------------------------------------------------------------------------"
make run --silent
if [ $? -eq 0 ]; then
    echo ""
else
    echo "Build failed."
fi