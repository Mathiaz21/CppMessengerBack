#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


class SocketHandler {
    
    private:
        int server_fd, new_socket;
        struct sockaddr_in address;
        int opt;
        int addrlen;
        char buffer[1024];
    public:

        // Utilities
        void sendHelloWorld();

        // Constructors
        SocketHandler();

        // Destructors
        ~SocketHandler();

};
