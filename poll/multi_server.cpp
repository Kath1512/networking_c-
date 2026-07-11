#include<arpa/inet.h>
#include<unistd.h>
#include<iostream>
#include<cstring>
#include<thread>
#include<poll.h>

void print_detail(const sockaddr_in& client_address){
    std::cout << "Client connected\n";
    std::cout << "Family: " << client_address.sin_family << "\n";
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_address.sin_addr, ip, INET_ADDRSTRLEN);
    std::cout << "Address: " << ip  << "\n";
}
bool get_client(int socket_fd, int& client_fd, sockaddr_in& client_address){
    socklen_t client_size = sizeof(client_address);
    client_fd = accept(
        socket_fd,
        reinterpret_cast<sockaddr*>(&client_address),
        &client_size
    );
    if(client_fd == -1){
        std::cout << "Error: " << strerror(errno) << "\n";
        return false;
    } 
    return true;
}

int main(){
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_fd == -1){
        std::cerr << "Error creating socket\n";
        std::cerr << "Error code: " << errno << '\n';
        std::cerr << strerror(errno) << '\n';
        return 1;
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    if(bind(socket_fd, 
            reinterpret_cast<sockaddr*>(&server_address),
            sizeof(server_address)) == -1){
        
        std::cerr << "Bind failed\n";
        std::cerr << strerror(errno) << '\n';
        close(socket_fd);
        return 1;
    }

    if(listen(socket_fd, 5) == -1){
        std::cerr << "Listen failed\n";
        std::cerr << strerror(errno) << '\n';
        close(socket_fd);
        return 1;
    }

    std::cout << "Listening on port 8080\n";

    
    std::vector<pollfd> fds;
    fds.push_back({socket_fd, POLLIN});

    while(true){
        poll(fds.data(), fds.size(), -1);
        for(auto& p : fds){
            if(p.revents & POLLIN){
                if(p.fd == socket_fd){
                    int client_fd;
                    sockaddr_in client_address{};
                    if(!get_client(socket_fd, client_fd, client_address)) return 1;
                    print_detail(client_address);
                    fds.push_back({client_fd, POLLIN});
                    std::cout << std::format("Waiting for message from client {}.....\n", client_fd);
                }
                else{
                    char buffer[256];
                    auto got = recv(p.fd, buffer, sizeof(buffer), 0);
                    if(got == 0){
                        std::cout << std::format("Connection fd {} closed\n", p.fd);
                        close(p.fd);
                        continue;
                    }
                    if(got == -1){
                        std::cerr << "Receive error: " << strerror(errno) << "\n";
                        return 1;
                    }

                    std::cout << std::format("Response from client {}: ", p.fd) << std::string(buffer, got) << "\n";
                    char response[] = "Got message!";
                    send(p.fd, response, sizeof(response), 0);
                }
            }
        }

    }

    close(socket_fd);


}

