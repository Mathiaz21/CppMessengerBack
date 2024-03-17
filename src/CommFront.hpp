#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


class SocketHandler {
    
    private:
        int server_fd, new_socket;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        char buffer[1024] = {0};

    public:

        void sendHelloWorld();

        // Constructors
        SocketHandler() : SocketHandler(0){}
        SocketHandler(int socketId);

        // Destructors
        ~SocketHandler();

};

class FrontCommunicator {
    private:
        SocketHandler sockets[8];
        unsigned int activeSockets;
    
    public:

        // Utilities
        int socketisActive(int socketId); // Returns 1 if socket is activated, 0 otherwise
        int activateSocket(int socketId);
        void sendHelloWorld(int socketId);


        //Constructors
        FrontCommunicator() : FrontCommunicator(8){}
        FrontCommunicator(int nbSockets);

        //Destructors
        ~FrontCommunicator();

};