#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <ctime>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "Datatypes.hpp"
#include "DbCommunication.hpp"

#ifndef COMM_FRONT
#define COMM_FRONT
class SocketHandler {
    
    private:
        int server_fd, new_socket;
        struct sockaddr_in address;
        int opt;
        int addrlen;
        int nb_bytes;
        char buffer[1024];
        int socketUserId;
    public:

        char *getBuffer();
        int getNbBytes();

        // Utilities
        void routeRequest(DbCommunicator dbCommunicator, char *sharedBuffer, int *bufferLen, int *threadSwitch, int *idUser);
        void sendConversation(int userd1, int userId2, DbCommunicator dbCommunicator);
        void translateFromBuffer(const std::string& encodedMessage, Message *message);
        void translateToBuffer(char *buffer, int *bufferLen, Message *message);
        void sendBuffer(char *buffer, int bufferLen);

        // Getters
        int getSocketUserId();

        // Setters
        void setUserId(int theUserId);
        // Constructors
        SocketHandler();

        // Destructors
        ~SocketHandler();

};

#endif // COMM_FRONT