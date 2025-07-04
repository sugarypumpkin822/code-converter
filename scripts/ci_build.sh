#!/bin/bash
set -e
cmake .
make -j$(nproc) 
