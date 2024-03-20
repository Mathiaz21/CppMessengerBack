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
std::time_t Message::getHeureEnvoi() { return this->heureEnvoi; };


// Setters
void Message::setMongoId(std::string newId) { this->mongoId = newId; };
void Message::setMessageId(int newId) { this->messageId = newId; };
void Message::setIdAuteur(int newId) { this->idAuteur = newId; };
void Message::setIdDestinataire(int newId) { this->idDestinataire = newId; };
void Message::setContenu(std::string newContenu) { this->contenu = newContenu; };
void Message::setHeureEnvoi(std::time_t newHeureEnvoi) { this->heureEnvoi = newHeureEnvoi; };

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

std::string Message::timeToString(std::time_t *time) {
  std::string timeStr;
  std::tm *timeInfo = std::localtime(time);
  timeStr += std::to_string(timeInfo->tm_mday) += "/";
  timeStr += std::to_string(timeInfo->tm_mon) += "/";
  timeStr += std::to_string(timeInfo->tm_year) += "/";

  int nbSeconds = timeInfo->tm_sec + 60*( timeInfo->tm_min + 60*( timeInfo->tm_hour ) );
  timeStr += std::to_string(nbSeconds);
  return timeStr;
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