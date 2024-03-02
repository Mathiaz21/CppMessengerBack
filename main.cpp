#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

#include "./src/DbCommunication.hpp"

#define DB_ADDRESS "mongodb://localhost:27017"


int main() {
    // Besoin d'initialilser ces paramètres dans le main :
    mongocxx::instance instance{};
    mongocxx::uri uri(DB_ADDRESS);
    mongocxx::client client(uri);
    mongocxx::database theDb = client["Messengerdb"];

    DbCommunicator dbCommunicator = DbCommunicator(theDb);

    int longueurConv = dbCommunicator.queryConversationLength(1,2);
    // std::cout << "Longueur de conv : " << longueurConv << "\n";
    Message messageList[longueurConv];
    dbCommunicator.queryConversation(messageList, longueurConv, 1,2);
    for(int i = 0; i < longueurConv; i++) {
        messageList[i].printMessage();
    }

    return 0;   
}