#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#include "Datatypes.hpp"

#ifndef DB_COMMINUCATION_HPP
#define DB_COMMUNICATION_HPP

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;


class DbCommunicator {

    private:
        mongocxx::database db;
        mongocxx::collection utilisateursCollection;
        mongocxx::collection conversationsCollection;
        mongocxx::collection messagesCollection;
        
        

    public:
        mongocxx::collection getUtilisateursCollection() { return this->utilisateursCollection; };
        mongocxx::collection getConversationsCollection() { return this->conversationsCollection; };
        mongocxx::collection getMessagesCollection() { return this->messagesCollection; };

        void addMessage(Message message);

    // Constructors
    DbCommunicator(mongocxx::database theDb) {
        this->db = theDb;
        this->utilisateursCollection = db["utilisateurs"];
        this->conversationsCollection = db["conversations"];
        this->messagesCollection = db["messages"];
    }
};

#endif // DB_COMMUNICATION_HPP