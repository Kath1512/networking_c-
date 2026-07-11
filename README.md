# networking_c++

Small C++ socket programming exercises using the POSIX sockets API on macOS.

## Layout

- `base_server/server.cpp` — minimal single-client TCP server (accepts one connection, prints client info).
- `base_client/client.cpp` — TCP client that connects to a server and sends a few messages a couple seconds apart.
- `poll/multi_server.cpp` — multi-client TCP server using `poll()` to multiplex client sockets.
- `kqueue/multi_server.cpp` — same multi-client server rewritten with `kqueue`, echoing a reply with a per-client message count.
- `run_command/` — build-and-run scripts for each version, one per binary.

Binaries are not checked in; each run script builds its target with `clang++` before running it.

## Run

```sh
run_command/run_base_server.sh     # base_server/server.cpp
run_command/run_base_client.sh     # base_client/client.cpp, launches 5 clients
run_command/run_poll_server.sh     # poll/multi_server.cpp
run_command/run_kqueue_server.sh   # kqueue/multi_server.cpp
```
