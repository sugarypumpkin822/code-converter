#!/bin/bash
set -e
find . -name '*.cpp' -o -name '*.h' | xargs clang-format -i 