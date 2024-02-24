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


    Message message = Message(346,2,1, "Oui et toi ?");

    DbCommunicator dbCommunicator = DbCommunicator(theDb);
    dbCommunicator.addMessage(message);

    return 0;   
}