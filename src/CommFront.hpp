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
        void routeRequest(DbCommunicator dbCommunicator);
        void sendConversation(int userd1, int userId2, DbCommunicator dbCommunicator);
        std::time_t stringToTime(const std::string& dateTimeStr);
        std::string timeToString(std::time_t *time);
        void translateFromBuffer(const std::string& encodedMessage, Message *message);
        void translateToBuffer(char *buffer, int *bufferLen, Message *message);


        // Getters
        int getSocketUserId();

        // Setters
        void setUserId(int theUserId);
        // Constructors
        SocketHandler();

        // Destructors
        ~SocketHandler();

};
