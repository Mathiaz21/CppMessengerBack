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
        int getIdMessage() { return this->idMessage; };
        int getIdAuteur() { return this->idAuteur; };
        int getIdDestinataire() { return this->idDestinataire; };
        std::string getContenu() { return this->contenu; };
        int getReaction() { return this->reaction; };
        std::time_t getHeureEnvoi() { return this->heureEnvoi; };
        std::time_t getHeureReception() { return this->heureReception; };
        std::time_t getHeureLecture() { return this->heureLecture; };
        

        // Setters
        void setIdMessage(int newId) { this->idMessage = newId; };
        void setIdAuteur(int newId) { this->idAuteur = newId; };
        void setIdDestinataire(int newId) { this->idDestinataire = newId; };
        void setContenu(std::string newContenu) { this->contenu = newContenu; };
        void setReaction(int newReaction) { this->reaction = newReaction; };
        void setHeureEnvoi(std::time_t newHeureEnvoi) { this->heureEnvoi = newHeureEnvoi; };
        void setHeureReception(std::time_t newHeureReception) { this->heureEnvoi = newHeureReception; };
        void setHeureLecture(std::time_t newHeureLecture) { this->heureLecture = newHeureLecture; };

        //Debugging
        void printMessage();

    // Constructors
    Message(int theIdMessage, int theIdAuteur, int theIdDestinataire) {
        this->idMessage = theIdMessage;
        this->idAuteur = theIdAuteur;
        this->idDestinataire = theIdDestinataire;
        this->contenu = "";
        this->heureEnvoi = time(0);
    }
    Message(int theIdMessage, int theIdAuteur, int theIdDestinataire, std::string theContenu) {
        this->idMessage = theIdMessage;
        this->idAuteur = theIdAuteur;
        this->idDestinataire = theIdDestinataire;
        this->contenu = theContenu;
        this->heureEnvoi = time(0);
    } 

    // Destructor
    ~Message() {};

};


class Conversation {

private:
    int idConv;
    int idFirstPers;
    int idSecPers;
    std::string convName;
    Message *messages;
    int convSize;

    std::string getConvName() {return this->convName; };
    int getConvSize() { return this->convSize; };
    // int getConvSize();

    void setName(std::string newName) {this->convName = newName; };
    void setConvSize(int newConvSize) {this->convSize = newConvSize; };
    // void addMsg(Message newMsg);
    // void editMsg(int idMsg, std::string newContent);
    // void deleteMsg(int idMsg);

public:
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