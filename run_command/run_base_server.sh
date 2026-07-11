#!/bin/sh
# Build and run the minimal single-client server (base_server/server.cpp)
cd "$(dirname "$0")/.." || exit 1
clang++ --std=c++20 base_server/server.cpp -o base_server/server
./base_server/server
