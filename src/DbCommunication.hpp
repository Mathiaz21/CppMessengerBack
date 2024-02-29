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

        // Variables
        mongocxx::database db;
        mongocxx::collection utilisateursCollection;
        mongocxx::collection conversationsCollection;
        mongocxx::collection messagesCollection;

    public:

        // Getters
        mongocxx::collection getUtilisateursCollection();
        mongocxx::collection getConversationsCollection();
        mongocxx::collection getMessagesCollection();

        // Mongo Queries
        void addMessage(Message message);

        void addUser(User user);
        void queryUserById(User *user, int theUserId);

    // Constructors
    DbCommunicator(mongocxx::database theDb);

    // Destructor
    ~DbCommunicator();
};

#endif // DB_COMMUNICATION_HPP