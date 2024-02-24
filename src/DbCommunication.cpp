#include "DbCommunication.hpp"

int insert_test_doc()  {
    mongocxx::instance instance{}; // This should be done only once.
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client client(uri);

    mongocxx::v_noabi::database db = client["Messengerdb"];
    mongocxx::collection collection = db["messages"];

    bsoncxx::v_noabi::document::value doc = make_document(
        kvp("Emetteur", "Alex"),
        kvp("Destinataire", "Mathias"),
        kvp("Contenu", "Salut ça va ?")
    );

    auto insert_one_result = collection.insert_one(make_document(kvp("i", 0)));


    return 0;   
}