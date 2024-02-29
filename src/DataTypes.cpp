#include "Datatypes.hpp"

/* * * * * * * * * * * * * * * * * * * * * * **/


// Getters
int Message::getIdMessage() { return this->idMessage; };
int Message::getIdAuteur() { return this->idAuteur; };
int Message::getIdDestinataire() { return this->idDestinataire; };
std::string Message::getContenu() { return this->contenu; };
int Message::getReaction() { return this->reaction; };
std::time_t Message::getHeureEnvoi() { return this->heureEnvoi; };
std::time_t Message::getHeureReception() { return this->heureReception; };
std::time_t Message::getHeureLecture() { return this->heureLecture; };


// Setters
void Message::setIdMessage(int newId) { this->idMessage = newId; };
void Message::setIdAuteur(int newId) { this->idAuteur = newId; };
void Message::setIdDestinataire(int newId) { this->idDestinataire = newId; };
void Message::setContenu(std::string newContenu) { this->contenu = newContenu; };
void Message::setReaction(int newReaction) { this->reaction = newReaction; };
void Message::setHeureEnvoi(std::time_t newHeureEnvoi) { this->heureEnvoi = newHeureEnvoi; };
void Message::setHeureReception(std::time_t newHeureReception) { this->heureEnvoi = newHeureReception; };
void Message::setHeureLecture(std::time_t newHeureLecture) { this->heureLecture = newHeureLecture; };

// Debugging
void Message::printMessage(){
    struct tm *ltm = localtime(&this->heureEnvoi);
    std::cout 
        << "_________\n"
        << "Message : \n"
        << "De : " << this->getIdAuteur() << "\n"
        << "Pour : " << this->getIdDestinataire() << "\n"
        << "Envoyé à " << ltm->tm_hour <<"h" << ltm->tm_min  
            << " le " << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << "\n\n"
        << this->getContenu() << "\n"
        << "_________\n\n";
}

// Constructors
Message::Message(int theIdMessage, int theIdAuteur, int theIdDestinataire) {
    this->idMessage = theIdMessage;
    this->idAuteur = theIdAuteur;
    this->idDestinataire = theIdDestinataire;
    this->contenu = "";
    this->heureEnvoi = time(0);
}
Message::Message(int theIdMessage, int theIdAuteur, int theIdDestinataire, std::string theContenu) {
    this->idMessage = theIdMessage;
    this->idAuteur = theIdAuteur;
    this->idDestinataire = theIdDestinataire;
    this->contenu = theContenu;
    this->heureEnvoi = time(0);
} 

//Destructor
Message::~Message(){};



/* * * * * * * * * * * * * * * * * * * * * * * * * * */

// Getters
int User::getId(){ return this->userId; };
std::string User::getPseudo(){ return this->pseudo; };
std::string User::getPassword(){ return this->password; };
bool User::testPassword(std::string testPassword) {return testPassword == this->password; };

// Setters
void User::setId(int theId) {this->userId = theId; };
void User::setPseudo(std::string thePseudo){this->pseudo = thePseudo; };
void User::setPassword(std::string thePassword){ this->password = thePassword; };

// Constructor
User::User(int theUserId, std::string thePseudo, std::string thePassword){
    this->userId = theUserId;
    this->pseudo = thePseudo;
    this->password = thePassword;
};

// Destructor
User::~User(){};