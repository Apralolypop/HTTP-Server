#include <arpa/inet.h>                  //Used for converting str to IP address
#include <iostream>                     
#include <netinet/in.h>                 //address structure
#include <sys/socket.h>                 //socket() functions
#include <unistd.h>                     //close()
#include <string.h>                     //strerror()
#include <cerrno>                       //Used for EINTR
#include <optional>                     //optional<T> data type that returns T or std::nullopt if invalid

// Header includes
#include "http_parser.h"

// Macro definitions
#define MAX_HEADER_SIZE 16384 // 16kb

// Data declarations

// Data definitions

// Function declarations

std::string read_request(int client_fd);

// Function definitions

// read_request reads the HTTP request and transforms it into a string
std::string read_request(int client_fd){
    std::string str = "";

    char buffer[1024];

    ssize_t bytes_received;

    while(true){
        bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);  // >0 receives bytes, 0 connection close, <0 error

        if(bytes_received == -1) {
            std::cerr << "recv failed\n";

            if(errno == EINTR) {
                continue;
            }
            return ""; // This returns 2 "\0", {"\0", "\0"}
        }else if(bytes_received == 0) {
            std::cout << "Client disconnected\n";
            return ""; // This returns 2 "\0", {"\0", "\0"}
        }else {
            std::cout << "read_request received " << bytes_received << " bytes: ";
            std::cout.write(buffer, bytes_received); //writes bytes_received bytes since the bytes sent doesn't have a '\0' at the end
            std::cout << std::endl;

            str.append(buffer, bytes_received); 
        }

        if(str.size() > MAX_HEADER_SIZE){
            std::cerr << "HTTP headers too large";
            close(client_fd);
            return "";
        }

        //Checks if the string ends with \r\n\r\n
        if(str.size() >= 4 && "\r\n\r\n" == str.substr(str.size() - 4)){
            break;
        }


    }

    return str;
}


// Main

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET decides if the socket is IPv4 or IPv6
    // IPv4 has 32bit address space, while IPv6 has 128bit address space.
    // SOCK_STREAM is a TCP socket, while SOCK_DGRAM is a UDP socket. 
    // Transport layer protocols are used to provide end-to-end communication between applications. 
    // TCP is a connection-oriented protocol that provides reliable data transfer, 
    // while UDP is a connectionless protocol that provides faster but less reliable data transfer.
    // It is less reliable because it does not guarantee that data packets arrive at destination, but it is still useful in the context of calls/games

    if (server_fd == -1) { // 
        std::cerr << "socket failed\n";
        return 1;
    }

    sockaddr_in address{}; //creates an address structure to hold the server's address information.
    //what does sockaddr_in contain? It contains the following fields:
    // sin_family: specifies the address family (AF_INET for IPv4)          2 bytes    
    // sin_port: specifies the port number                                  2 bytes  
    // sin_addr: specifies the IP address                                   4 bytes
    // sin_zero: padding to make the structure the same size as sockaddr    8 bytes
    
    address.sin_family = AF_INET;
    address.sin_port = htons(8080); // Host to network short
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // which is 127.0.0.1

    
    if (bind(server_fd, //server_fd is a file descriptor that represents the socket created earlier.
        // a file descriptor is something that represents an open file, socket, or other resource in the operating system.
             reinterpret_cast<sockaddr*>(&address), // converts address to a sockaddr pointer
             sizeof(address)) == -1) //If there is an error, we close the server
    {
        std::cerr << "bind failed\n";
        close(server_fd); // closes the socket file descriptor to free up system resources.
        return 1;
    }

    if (listen(server_fd, 10) == -1) { //10, requests a backlog of 10 connections, which means that the server can handle up to 10 incoming connections at once.
        std::cerr << "listen failed\n";
        close(server_fd);
        return 1;
    }

    
    std::cout << "Listening on 127.0.0.1:8080\n";
    

    sockaddr_in client_address{}; //creates another sockaddr_in structure
    socklen_t client_length = sizeof(client_address); 
    //Creates that holds the size of the client address structure, which is used later when accepting a connection from a client.
    // The size is 16 bytes, which is the size of the sockaddr_in structure.

    // Program stops here and waits until there is a connection
    int client_fd = accept(server_fd, reinterpret_cast<sockaddr*>(&client_address), &client_length); //Two pass by pointer

    if(client_fd == -1) {
        std::cerr << "accept failed\n";
        close(server_fd);
        return 1;
    }

    std::cout << "Client connected\n";


    //recv(client_fd, buffer, sizeof(buffer), 0) receives data from client
    //send(client_fd, buffer, sizeof(buffer), 0) sends data to client
    //

    while(true){


        char buffer[25];

        ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);  // >0 receives bytes, 0 connection close, <0 error
        //NOTE The received buffer also receive '\n'

        if(bytes_received == -1) {
            std::cerr << "recv failed\n";
            close(client_fd);
            close(server_fd);
            return 1;
        }else if(bytes_received == 0) {
            std::cout << "Client disconnected\n";
            close(client_fd);
            close(server_fd);
            return 0;
        }else {
            buffer[bytes_received] = '\0'; // Null-terminate the buffer to make it a valid C-string
            std::cout << "Received " << bytes_received << " bytes: ";
            std::cout.write(buffer, bytes_received); //writes bytes_received bytes since the bytes sent doesn't have a '\0' at the end
            std::cout << std::endl;

            if(strcmp(buffer, "terminate") == 0){ //THIS DOESNT WORK BECAUSE NC SEND SOME THINGS after terminate
                std::cout << "Exiting...\n";
                break;
            }

            ssize_t bytes_sent = send(client_fd, buffer, bytes_received, 0);  // >0 sends bytes, 0 connection close, <0 error

            if (bytes_sent == -1) {
                perror("send"); // Print the error message 
                break;
            }
        }
    

    }


/* 
    while (true) {
    sockaddr_in client_address{};
    socklen_t client_length = sizeof(client_address);

    int client_fd = accept(
        server_fd,
        reinterpret_cast<sockaddr*>(&client_address),
        &client_length
    );

    if (client_fd == -1) {
        std::cerr << "accept failed\n";
        continue;
    }

    std::cout << "Client connected!" << std::endl;

    close(client_fd);
}
*/


/*
An HHTP request looks like this:
GET / HTTP/1.1
Host: 127.0.0.1:8080
User-Agent: curl/8.x
*/ //Accept: */* without */ //




    close(client_fd);
    close(server_fd);
    return 0;
}
