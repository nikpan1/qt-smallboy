#!/bin/bash


find . -name "*.cpp" -o -name "*.h" | xargs clang-format -i

cmake --build src/
