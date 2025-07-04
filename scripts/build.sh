#!/bin/bash
set -e
qmake CodeTranslator.pro
make -j$(nproc)
echo "Build complete." 