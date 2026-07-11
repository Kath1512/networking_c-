#!/bin/sh
# Build and run the poll()-based multi-client server (poll/multi_server.cpp)
cd "$(dirname "$0")/.." || exit 1
clang++ --std=c++20 poll/multi_server.cpp -o poll/multi_server
./poll/multi_server
