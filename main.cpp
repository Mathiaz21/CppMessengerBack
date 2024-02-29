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

    User utilisateur = User(1, "Vide", "Vide");
    dbCommunicator.queryUserById(&utilisateur, 1);
    std::cout << utilisateur.getPseudo() << utilisateur.getPassword() <<"\n\n";

    return 0;   
}