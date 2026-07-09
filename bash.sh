clang++ --std=c++20 multi_server.cpp -o multi_server
clang++ --std=c++20 client.cpp -o client &&
# ./server &
# sleep 0.2
# ./client