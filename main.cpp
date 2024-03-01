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

    Message message = Message(1,2,"Je mange des frites");
    dbCommunicator.addMessage(message);

    int longueurConv = dbCommunicator.queryConversationLength(1,2);
    std::cout << longueurConv << "\n";

    return 0;   
}