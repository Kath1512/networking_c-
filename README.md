# networking_c++

Small C++ socket programming exercises using the POSIX sockets API on macOS.

## Files

- `server.cpp` — minimal single-client TCP server (accepts one connection, prints client info).
- `client.cpp` — TCP client that connects to a server and sends a few messages a couple seconds apart.
- `poll/multi_server.cpp` — multi-client TCP server using `poll()` to multiplex client sockets.
- `kqueue/multi_server.cpp` — same multi-client server rewritten with `kqueue`, echoing a reply with a per-client message count.

## Build

```sh
clang++ -std=c++20 server.cpp -o server
clang++ -std=c++20 client.cpp -o client
clang++ -std=c++20 poll/multi_server.cpp -o poll/multi_server
clang++ -std=c++20 kqueue/multi_server.cpp -o kqueue/multi_server
```

## Run

```sh
./poll/multi_server     # or ./kqueue/multi_server, or ./server
./client <name>
```
