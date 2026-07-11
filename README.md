# networking_c++

Small C++ socket programming exercises using the POSIX sockets API on macOS.

## Files

- `server.cpp` — minimal single-client TCP server (accepts one connection, prints client info).
- `multi_server.cpp` — multi-client TCP server on port 8080, using `kqueue` to handle many concurrent client connections and echo a reply with a per-client message count.
- `client.cpp` — TCP client that connects to the server and sends a few messages a couple seconds apart.

## Build

```sh
g++ -std=c++20 server.cpp -o server
g++ -std=c++20 multi_server.cpp -o multi_server
g++ -std=c++20 client.cpp -o client
```

## Run

```sh
./multi_server   # or ./server
./client <name>
```
