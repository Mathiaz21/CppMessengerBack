#include "DbCommunication.hpp"


// Getters
mongocxx::collection DbCommunicator::getUtilisateursCollection() { return this->utilisateursCollection; };
mongocxx::collection DbCommunicator::getConversationsCollection() { return this->conversationsCollection; };
mongocxx::collection DbCommunicator::getMessagesCollection() { return this->messagesCollection; };


// Queries
void DbCommunicator::addMessage(Message message) {
    this->getMessagesCollection().insert_one(make_document(
        kvp("idAuteur", message.getIdAuteur()),
        kvp("idDestinataire", message.getIdDestinataire()),
        kvp("contenu", message.getContenu())
    ));
}

void DbCommunicator::addUser(User user) {
    this->getUtilisateursCollection().insert_one(make_document(
        kvp("idUtilisateur", user.getId()),
        kvp("pseudo", user.getPseudo()),
        kvp("password", user.getPassword())
    ));
}


void DbCommunicator::queryUserById(User *user, int theUserId) {
    auto userDoc = this->getUtilisateursCollection()
        .find_one(make_document("userId", theUserId));
    bsoncxx::document::view userView = userDoc->view();
    (*user).setId(userView["userId"].get_int32().value);
    (*user).setPseudo(userView["pseudo"].get_utf8().value.to_string());
    (*user).setPassword(userView["password"].get_utf8().value.to_string());
}



DbCommunicator::DbCommunicator(mongocxx::database theDb) {
    this->db = theDb;
    this->utilisateursCollection = db["utilisateurs"];
    this->conversationsCollection = db["conversations"];
    this->messagesCollection = db["messages"];
};

DbCommunicator::~DbCommunicator(){};