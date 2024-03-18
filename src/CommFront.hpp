#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "Datatypes.hpp"


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

        // Utilities
        void recvNSave();
        std::time_t stringToTime(const std::string& dateTimeStr);
        void translateFromBuffer(const std::string& encodedMessage, Message *message);


        // Getters
        int getSocketUserId();

        // Setters
        void setUserId(int theUserId);
        // Constructors
        SocketHandler();

        // Destructors
        ~SocketHandler();

};
