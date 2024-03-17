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
        int main_socket, front_socket;
        struct sockaddr_in server_address;
        int bytes_in_buffer;
        char buffer[1024];

    public:

        void recvNPrint();
        void initialiseClientSocket();
        void closeFrontSocket();

        // Constructors
        SocketHandler();

        // Destructors
        ~SocketHandler();

};
