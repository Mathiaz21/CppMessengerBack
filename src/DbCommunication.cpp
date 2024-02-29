#include "DbCommunication.hpp"

void DbCommunicator::addMessage(Message message) {
    this->getMessagesCollection().insert_one(make_document(
        kvp("idAuteur", message.getIdAuteur()),
        kvp("idDestinataire", message.getIdDestinataire()),
        kvp("contenu", message.getContenu())
    ));
}
void DbCommunicator::getMessage(Message *message, char *id){
    auto message = this->getMessagesCollection().find_one({});
}


mongocxx::collection DbCommunicator::getUtilisateursCollection() { return this->utilisateursCollection; };
mongocxx::collection DbCommunicator::getConversationsCollection() { return this->conversationsCollection; };
mongocxx::collection DbCommunicator::getMessagesCollection() { return this->messagesCollection; };


DbCommunicator::DbCommunicator(mongocxx::database theDb) {
    this->db = theDb;
    this->utilisateursCollection = db["utilisateurs"];
    this->conversationsCollection = db["conversations"];
    this->messagesCollection = db["messages"];
};

DbCommunicator::~DbCommunicator(){};