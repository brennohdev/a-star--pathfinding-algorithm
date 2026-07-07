#!/bin/bash
set -e

echo "configuring.."
cmake -B build -DCMAKE_BUILD_TYPE=Release

echo "buuilding..."
cmake --build build --parallel $(sysctl -n hw.ncpu 2>/dev/null || nproc)

echo ""
echo "done, run with: ./build/app"
