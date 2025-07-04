#!/bin/bash
set -e
for test in tests/test_*.cpp; do
    exe="${test%.cpp}"
    g++ -std=c++17 -I. -I/usr/include/qt -I/usr/include/qt/QtTest -fPIC $test -o $exe -lQt5Test -lQt5Core
    ./$exe
done
echo "All tests completed." 