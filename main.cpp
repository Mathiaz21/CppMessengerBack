#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include "./src/CommFront.hpp"

#define DB_ADDRESS "mongodb://localhost:27017"

void boucle_principale(mongocxx::database db, int idThread, int *bufferLen, int *threadSwitch, char *sharedBuffer) {
    // Allocation temporaire de idUser à Idthread
    int idUser = idThread;
    DbCommunicator dbCommunicator = DbCommunicator(db);
    Message message;
    while(true) {
        SocketHandler socketHandler = SocketHandler();
        while (true)
        {
            socketHandler.routeRequest(dbCommunicator, sharedBuffer, bufferLen, threadSwitch, &idUser);
            if(socketHandler.getNbBytes() <= 0){
                std::cout <<"Client déconnecté\n";
                break;
            }
            // Cas où le thread doit partager un message
            if(*threadSwitch==idUser){
                socketHandler.sendBuffer(sharedBuffer, *bufferLen);
                *threadSwitch = -2; // Retour à la valeur par défaut
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

    char *sharedBuffer = new char[1024];
    int bufferLen;
    int threadSwitch = -2;

    // std::string encodedMessage = "{I:{1},A:{1},D:{2},S:{17/03/2024/80000},C:{Bonjour Mme Pavoshko moi je fais des hits Mme Pavoshko}}";
    std::thread t1([theDb, &bufferLen, &threadSwitch, sharedBuffer ]() {boucle_principale(theDb, 1, &bufferLen, &threadSwitch, sharedBuffer ); });
    std::thread t2([theDb, &bufferLen, &threadSwitch, sharedBuffer ]() {boucle_principale(theDb, 2, &bufferLen, &threadSwitch, sharedBuffer ); });
    std::thread t3([theDb, &bufferLen, &threadSwitch, sharedBuffer ]() {boucle_principale(theDb, 3, &bufferLen, &threadSwitch, sharedBuffer ); });
    std::thread t4([theDb, &bufferLen, &threadSwitch, sharedBuffer ]() {boucle_principale(theDb, 4, &bufferLen, &threadSwitch, sharedBuffer ); });
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