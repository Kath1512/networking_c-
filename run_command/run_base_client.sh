#!/bin/sh
# Build and run 5 client instances against a running server (base_client/client.cpp)
cd "$(dirname "$0")/.." || exit 1
clang++ --std=c++20 base_client/client.cpp -o base_client/client

for i in $(seq 1 5); do
    ./base_client/client "AlexTrinh_${i}" &
done

wait
