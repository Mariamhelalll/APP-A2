#!/bin/bash
set -e
cd src
g++ -std=c++17 -Wall -Wextra -Wpedantic -g -o ../library *.cpp
echo "Build OK. Run with ./library"