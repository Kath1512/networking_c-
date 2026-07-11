#!/bin/sh
# Build and run the kqueue-based multi-client server (kqueue/multi_server.cpp)
cd "$(dirname "$0")/.." || exit 1
clang++ --std=c++20 kqueue/multi_server.cpp -o kqueue/multi_server
./kqueue/multi_server
