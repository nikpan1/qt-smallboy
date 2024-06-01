#!/bin/bash

find . -name "*.cpp" -o -name "*.h" | xargs clang-format -i

# cmake --build src/

./src/build/qt-smallboy &
./src/build/qt-smallboy &

wait

echo "All done"
