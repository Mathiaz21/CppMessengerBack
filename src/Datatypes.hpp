#include <string>
#include <ctime>
#include <iostream>

#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

class Message {

    private:
        // Variables 
        int idMessage;
        int idAuteur;
        int idDestinataire;
        std::string contenu;
        int reaction;
        std::time_t heureEnvoi;
        std::time_t heureReception;
        std::time_t heureLecture;

    public:
        // Getters
        int getIdMessage();
        int getIdAuteur();
        int getIdDestinataire();
        std::string getContenu();
        int getReaction();
        std::time_t getHeureEnvoi();
        std::time_t getHeureReception();
        std::time_t getHeureLecture();
        

        // Setters
        void setIdMessage(int newId);
        void setIdAuteur(int newId);
        void setIdDestinataire(int newId);
        void setContenu(std::string newContenu);
        void setReaction(int newReaction);
        void setHeureEnvoi(std::time_t newHeureEnvoi);
        void setHeureReception(std::time_t newHeureReception);
        void setHeureLecture(std::time_t newHeureLecture);

        //Debugging
        void printMessage();

    // Constructors
    Message(int theIdMessage, int theIdAuteur, int theIdDestinataire);
    Message(int theIdMessage, int theIdAuteur, int theIdDestinataire, std::string theContenu);

    // Destructor
    ~Message();

};


class Conversation {

private:
    int idConv;
    int idFirstPers;
    int idSecPers;
    std::string convName;
    Message *messages;
    int convSize;

public:
    std::string getConvName() {return this->convName; };
    int getConvSize() { return this->convSize; };

    void setName(std::string newName) {this->convName = newName; };
    void setConvSize(int newConvSize) {this->convSize = newConvSize; };
    // void addMsg(Message newMsg);
    // void editMsg(int idMsg, std::string newContent);
    // void deleteMsg(int idMsg);

    // Constructors
    Conversation(int theIdConv, int theIdFirstPers, int theIdSecPers, std::string theConvName){
        this->idConv = theIdConv;
        this->idFirstPers = theIdFirstPers;
        this->idSecPers = theIdSecPers;
        this->convName = theConvName;
    };

    Conversation(int theIdConv, int theIdFirstPers, int theIdSecPers, std::string theConvName, Message* theMessages, int theConvSize){
        this->idConv = theIdConv;
        this->idFirstPers = theIdFirstPers;
        this->idSecPers = theIdSecPers;
        this->convName = theConvName;
        this->messages = theMessages;
        this->convSize = theConvSize;
    };

    ~Conversation(){};
};


#endif //DATA_TYPES_HPP