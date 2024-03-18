#include "Datatypes.hpp"

/*  * * * * * * * * * * * * * * * * * * * * *

* * * * * * * * * MESSAGES  * * * * * * * * *

* * * * * * * * * * * * * * * * * * * * * * */


// Getters
std::string Message::getMongoId() { return this->mongoId; };
int Message::getMessageId() {return this->messageId; };
int Message::getIdAuteur() { return this->idAuteur; };
int Message::getIdDestinataire() { return this->idDestinataire; };
std::string Message::getContenu() { return this->contenu; };
int Message::getReaction() { return this->reaction; };
std::time_t Message::getHeureEnvoi() { return this->heureEnvoi; };
std::time_t Message::getHeureReception() { return this->heureReception; };
std::time_t Message::getHeureLecture() { return this->heureLecture; };


// Setters
void Message::setMongoId(std::string newId) { this->mongoId = newId; };
void Message::setMessageId(int newId) { this->messageId = newId; };
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

// Utilities
void Message::copyMessage(Message newMessage) {
    this->setMongoId( newMessage.getMongoId() );
    this->setIdAuteur( newMessage.getIdAuteur() );
    this->setIdDestinataire( newMessage.getIdDestinataire() );
    this->setContenu( newMessage.getContenu() );
    this->setHeureEnvoi( newMessage.getHeureEnvoi() );
    this->setHeureReception( newMessage.getHeureReception() );
    this->setHeureLecture( newMessage.getHeureLecture() );
    this->setReaction( newMessage.getReaction() );
}

std::time_t Message::stringToTime(const std::string& dateTimeStr) {
    std::tm time = {};
    std::stringstream ss(dateTimeStr);
    char delimiter;
    ss >> time.tm_mday >> delimiter >> time.tm_mon >> delimiter >> time.tm_year >> delimiter;
    int secondsOfDay;
    ss >> secondsOfDay;
    time.tm_year -= 1900;
    time.tm_mon -= 1;
    time.tm_sec = secondsOfDay % 60;
    secondsOfDay /= 60;
    time.tm_min = secondsOfDay % 60;
    time.tm_hour = secondsOfDay / 60;
    return std::mktime(&time);
}

void Message::translateFromBuffer(const std::string& encodedMessage) {
    size_t pos = encodedMessage.find("I:{");
    if (pos == std::string::npos)
        return; 

    size_t posEnd = encodedMessage.find("},", pos);
    if (posEnd == std::string::npos)
        return; 
    std::string messageIdStr = encodedMessage.substr(pos + 3, posEnd - pos - 3);
    setMessageId(std::stoi(messageIdStr));

    pos = encodedMessage.find("A:{");
    if (pos == std::string::npos)
        return;
    posEnd = encodedMessage.find("},", pos);
    if (posEnd == std::string::npos)
        return;
    std::string idAuteurStr = encodedMessage.substr(pos + 3, posEnd - pos - 3);
    setIdAuteur(std::stoi(idAuteurStr));

    pos = encodedMessage.find("D:{");
    if (pos == std::string::npos)
        return;
    posEnd = encodedMessage.find("},", pos);
    if (posEnd == std::string::npos)
        return;
    std::string idDestinataireStr = encodedMessage.substr(pos + 3, posEnd - pos - 3);
    setIdDestinataire(std::stoi(idDestinataireStr));

    pos = encodedMessage.find("S:{");
    if (pos == std::string::npos)
        return;
    posEnd = encodedMessage.find("},", pos);
    if (posEnd == std::string::npos)
        return;
    std::string heureEnvoiStr = encodedMessage.substr(pos + 3, posEnd - pos - 3);
    setHeureEnvoi(stringToTime(heureEnvoiStr));

    pos = encodedMessage.find("C:{");
    if (pos == std::string::npos)
        return;
    posEnd = encodedMessage.find("}}", pos);
    if (posEnd == std::string::npos)
        return;
    std::string contenuStr = encodedMessage.substr(pos + 3, posEnd - pos - 3);
    setContenu(contenuStr);
}

// Constructors
Message::Message() {};
Message::Message(std::string theMongoId, int theMessageId, int theIdAuteur, int theIdDestinataire) {
    this->mongoId = theMongoId;
    this->messageId = theMessageId;
    this->idAuteur = theIdAuteur;
    this->idDestinataire = theIdDestinataire;
    this->contenu = "";
    this->heureEnvoi = time(0);
}
Message::Message(std::string theMongoId, int theMessageId, int theIdAuteur, int theIdDestinataire, std::string theContenu) {
    this->mongoId = theMongoId;
    this->messageId = theMessageId;
    this->idAuteur = theIdAuteur;
    this->idDestinataire = theIdDestinataire;
    this->contenu = theContenu;
    this->heureEnvoi = time(0);
} 
Message::Message(int theIdAuteur, int theIdDestinataire, std::string theContenu){
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

// Utilities
void User::copyUser(User newUser) {
    this->setId( newUser.getId() );
    this->setPseudo( newUser.getPseudo() );
    this->setPassword( newUser.getPassword() );
}

// Constructor
User::User(){};
User::User(int theUserId, std::string thePseudo, std::string thePassword){
    this->userId = theUserId;
    this->pseudo = thePseudo;
    this->password = thePassword;
};

// Destructor
User::~User(){};