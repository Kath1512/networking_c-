#include<arpa/inet.h>
#include<unistd.h>
#include<iostream>
#include<cstring>

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

    sockaddr_in client_address{};
    socklen_t client_size = sizeof(client_address);
    int client_fd = accept(
        socket_fd,
        reinterpret_cast<sockaddr*>(&client_address),
        &client_size
    );

    std::cout << "Client connected\n";
    std::cout << "Family: " << client_address.sin_family << "\n";
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_address.sin_addr, ip, INET_ADDRSTRLEN);
    std::cout << "Address: " << ip  << "\n";
    
    std::cout << "Waiting for message.....\n";
    char response[256];
    recv(client_fd, response, sizeof(response), MSG_EOR);   

    std::cout << "Response from client: " << response << "\n";

    close(socket_fd);


}

