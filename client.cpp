#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <chrono>

int main(int arc, char* argv[]){
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1){
        std::cerr << "Socket error\n";
        std::cerr << strerror(errno) << "\n";
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    if(connect(socket_fd, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) == -1){
        std::cerr << "Connection error\n";
        std::cerr << strerror(errno) << "\n";
    }
    int count = 0;
    while(count++ < 4){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::string message = std::format("Hello server from {}\n", argv[1]);
        auto sz = send(socket_fd, message.data(), message.size(), 0);
        if(sz == -1){
            std::cerr << "Sent error\n";
            std::cerr << strerror(errno) << "\n";
        }
        std::cout << "Sent: " << sz << "\n";
        char buffer[256];
        auto got = recv(socket_fd, buffer, sizeof(buffer), 0);
        std::cout << "Got: " << got << "\n";
        if(got == 0){
            std::cout << "Connection closed\n";
        }
        if(got == -1){
            std::cerr << "Error: " << strerror(errno) << "\n";
            return 1;
        }

        std::cout << "Response from server: ";
        std::cout.write(buffer, got);
        std::cout << "\n";
        
    }
    close(socket_fd);
    return 0;
}