#include <cstdint>
#include <iostream>
#include <vector>
#include <string>


#include "./src/DbCommunication.hpp"
#include "./src/CommFront.hpp"

#define DB_ADDRESS "mongodb://localhost:27017"


int main() {
    // Besoin d'initialilser ces paramètres dans le main :
    mongocxx::instance instance{};
    mongocxx::uri uri(DB_ADDRESS);
    mongocxx::client client(uri);
    mongocxx::database theDb = client["Messengerdb"];

    DbCommunicator dbCommunicator = DbCommunicator(theDb);
    while(true){
        SocketHandler socketHandler = SocketHandler();
        socketHandler.sendHelloWorld();
    }
    
    /*
    int longueurConv = dbCommunicator.queryConversationLength(1,2);
    Message messageList[longueurConv];
    dbCommunicator.queryConversation(messageList, longueurConv, 1,2);
    for(int i = 0; i < longueurConv; i++) {
        messageList[i].printMessage();
    }*/

    /*
    int nbUsers = dbCommunicator.queryNumberOfUsers();
    std::cout << "Nb users : " << nbUsers << "\n";
    User userList[nbUsers];
    dbCommunicator.queryUserList(userList, nbUsers);
    for( User user: userList) {
        std::cout << "Utilisateur : " << user.getPseudo() << "\n";
    }
    */
    // dbCommunicator.deleteConversation(1,2);
    return 0;   
}