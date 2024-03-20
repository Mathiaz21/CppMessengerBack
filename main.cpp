#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

#include "./src/CommFront.hpp"

#define DB_ADDRESS "mongodb://localhost:27017"

void boucle_principale(mongocxx::database db, int idThread) {
    DbCommunicator dbCommunicator = DbCommunicator(db);
    Message message;
    while(true) {
        SocketHandler socketHandler = SocketHandler();
        std::cout << "Connexions au Thread : " << idThread << "\n";
        while (true)
        {
            socketHandler.routeRequest(dbCommunicator);
            if(socketHandler.getNbBytes() <= 0){
                std::cout << "Client a fermé la connexion ou erreur\n";
                break;
            }
        }
    }
}


int main() {
    // Besoin d'initialilser ces paramètres dans le main :
    mongocxx::instance instance{};
    mongocxx::uri uri(DB_ADDRESS);
    mongocxx::client client(uri);
    mongocxx::database theDb = client["Messengerdb"];

    // std::string encodedMessage = "{I:{1},A:{1},D:{2},S:{17/03/2024/80000},C:{Bonjour Mme Pavoshko moi je fais des hits Mme Pavoshko}}";
    std::thread t1([theDb]() {boucle_principale(theDb, 1); });
    std::thread t2([theDb]() {boucle_principale(theDb, 2); });
    std::thread t3([theDb]() {boucle_principale(theDb, 3); });
    std::thread t4([theDb]() {boucle_principale(theDb, 4); });
    // socketHandler.sendConversation(1, -1, dbCommunicator);
    t1.join();
	t2.join();
    t3.join();
    t4.join();

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
};