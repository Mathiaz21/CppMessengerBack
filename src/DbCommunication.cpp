#include "DbCommunication.hpp"


// Getters
mongocxx::collection DbCommunicator::getUtilisateursCollection() { return this->utilisateursCollection; };
mongocxx::collection DbCommunicator::getConversationsCollection() { return this->conversationsCollection; };
mongocxx::collection DbCommunicator::getMessagesCollection() { return this->messagesCollection; };


// Queries
void DbCommunicator::addMessage(Message message) {
    std::time_t heureEnvoi = message.getHeureEnvoi();

    this->getMessagesCollection().insert_one(make_document(
        kvp("idMessage", message.getMessageId()),
        kvp("idAuteur", message.getIdAuteur()),
        kvp("idDestinataire", message.getIdDestinataire()),
        kvp("heureDenvoi", message.timeToString(&heureEnvoi)),
        kvp("contenu", message.getContenu())
    ));
}

void DbCommunicator::deleteMessageById(std::string messageId) {
    this->getMessagesCollection().delete_one(make_document(kvp("_id", bsoncxx::oid(messageId))));
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

void DbCommunicator::deleteConversation(int theUserId1, int theUserId2) {
    int convLength = queryConversationLength(theUserId1, theUserId2);
    Message messageList[convLength];
    queryConversation(messageList, convLength, theUserId1, theUserId2);
    for(Message message: messageList){
        std::string messageId = message.getMongoId();
        deleteMessageById(messageId);
    }
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

int DbCommunicator::queryNumberOfUsers() {
    int result = 0;
    auto cursor = this->getUtilisateursCollection().find( {} );
    for( auto doc: cursor){
        result++;
    }
    return result;
}

void DbCommunicator::queryUserList(User *userList, int nbOfUsers) {
    int count = 0;
    auto cursor = this->getUtilisateursCollection().find({});
    for(auto messageView: cursor){
        if(count < nbOfUsers) {
            User userBuffer;
            setUserFromView(&userBuffer, messageView);
            userList[count].copyUser(userBuffer);
            count++;
        }
    }
}


// Utilities
void DbCommunicator::setMessageFromView(Message *message, bsoncxx::v_noabi::document::view view) {
    std::string theMongoId = view["_id"].get_oid().value.to_string();
    int theMessageId = view["idMessage"].get_int32().value;
    int theSenderId = view["idAuteur"].get_int32().value;
    int theReceiverId = view["idDestinataire"].get_int32().value;
    std::string theContent = view["contenu"].get_string().value.to_string();
    std::string heureDenvoi = view["heureDenvoi"].get_string().value.to_string();

    message->setMongoId( theMongoId );
    message->setMessageId( theMessageId );
    message->setIdAuteur( theSenderId );
    message->setIdDestinataire( theReceiverId );
    message->setHeureEnvoi( message->stringToTime(heureDenvoi) );
    message->setContenu( theContent );

}

void DbCommunicator::setUserFromView(User *user, bsoncxx::v_noabi::document::view view){
    int theUserId = view["userId"].get_int32().value;
    std::string thePseudo = view["pseudo"].get_string().value.to_string();
    std::string thePassword = view["password"].get_string().value.to_string();
    
    user->setId( theUserId );
    user->setPseudo( thePseudo );
    user->setPassword (thePassword );
}


// Constructor
DbCommunicator::DbCommunicator(mongocxx::database theDb) {
    this->db = theDb;
    this->utilisateursCollection = db["utilisateurs"];
    this->conversationsCollection = db["conversations"];
    this->messagesCollection = db["messages"];
};

// Destructor
DbCommunicator::~DbCommunicator(){};