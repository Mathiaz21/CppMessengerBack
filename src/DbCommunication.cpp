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

int DbCommunicator::queryConversationLength(int theUserId1, int theUserId2){
    int result = 0;
    int ids[2] = {theUserId1, theUserId2};
    for(int i = 0; i < 2; ++i){

        bsoncxx::builder::basic::document query_builder;
        query_builder.append(kvp("idAuteur", ids[i]));
        query_builder.append(kvp("idDestinataire", ids[1 - i]));

        auto query_filter = query_builder.extract();
        auto cursor = this->getMessagesCollection().find( query_filter.view() );
        for( auto doc: cursor){
            result++;
            // std::cout << doc["contenu"].get_string().value.to_string();
        }
    }
    return result;
}

void DbCommunicator::queryConversation(Message *messageList, int convLen, int theUserId1, int theUserId2){
    int ids[2] = {theUserId1, theUserId2};
    int count = 0;
    for(int i = 0; i < 2; ++i){
        bsoncxx::builder::basic::document query_builder;
        query_builder.append(kvp("idAuteur", ids[i]));
        query_builder.append(kvp("idDestinataire", ids[1 - i]));
        auto query_filter = query_builder.extract();
        auto cursor = this->getMessagesCollection().find( query_filter.view());
        for(auto messageView: cursor){
            if(count < convLen){
                Message messageBuffer;
                setMessageFromView(&messageBuffer, messageView);
                messageList[count].copyMessage(messageBuffer);
                count++;
            }
        }
    };

}

void DbCommunicator::deleteMessageById(std::string messageId) {
    this->getMessagesCollection().delete_one(make_document(kvp("_id", bsoncxx::oid(messageId))));
}

void DbCommunicator::addUser(User user) {
    this->getUtilisateursCollection().insert_one(make_document(
        kvp("userId", user.getId()),
        kvp("pseudo", user.getPseudo()),
        kvp("password", user.getPassword())
    ));
}


void DbCommunicator::queryUserById(User *user, int theUserId) {
    auto userDoc = this->getUtilisateursCollection()
        .find_one( make_document(kvp("userId", theUserId)));
    bsoncxx::document::view userView = userDoc->view();
    std::string thePseudo = userView["pseudo"].get_string().value.to_string();
    std::string thePassword = userView["password"].get_string().value.to_string();

    (*user).setId( theUserId);
    (*user).setPseudo( thePseudo );
    (*user).setPassword( thePassword );
}


void DbCommunicator::setMessageFromView(Message *message, bsoncxx::v_noabi::document::view view) {
    std::string theMessageId = view["_id"].get_oid().value.to_string();
    int theSenderId = view["idAuteur"].get_int32().value;
    int theReceiverId = view["idDestinataire"].get_int32().value;
    std::string theContent = view["contenu"].get_string().value.to_string();
    message->setIdMessage( theMessageId );
    message->setIdAuteur( theSenderId );
    message->setIdDestinataire( theReceiverId );
    message->setContenu( theContent );

}


DbCommunicator::DbCommunicator(mongocxx::database theDb) {
    this->db = theDb;
    this->utilisateursCollection = db["utilisateurs"];
    this->conversationsCollection = db["conversations"];
    this->messagesCollection = db["messages"];
};

DbCommunicator::~DbCommunicator(){};