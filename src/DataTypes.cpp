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

int assertChar(char character, char *buffer, int cursor) {
    if(buffer[cursor] == character) {
        return 0;
    }
    std::cerr << "Error, waiting for " << character
    << " but got " << buffer[cursor] << "\n";
    return 1;
}

int Message::unpackInt(char *buffer, int *cursor, char flag){
    if( assertChar( flag, buffer, *cursor) == 1){
        return 1;
    }
    *cursor++;
    if( assertChar( ':', buffer, *cursor) == 1){
        return 1;
    }
    *cursor++;
    char receptor[128];
    int count = 0;
    while(buffer[*cursor] != '}') {
        receptor[count] = buffer[*cursor];
        *cursor++;
        count++;
    }
    receptor[count] = '\0';
    *cursor++;
    int result = std::stoi(buffer);
    return result;
}

std::string unpackString(char *buffer, int *cursor, char flag) {
    if( assertChar( flag, buffer, *cursor) == 1){
        return;
    }
    *cursor++;
    if( assertChar( ':', buffer, *cursor) == 1){
        return;
    }
    *cursor++;
    char receptor[128];
    int count = 0;
    while(buffer[*cursor] != '}') {
        receptor[count] = buffer[*cursor];
        *cursor++;
        count++;
    }
    receptor[count] = '\0';
    *cursor++;
    std::string result = receptor;
    return result;
}

std::time_t unpackTime(char *buffer, int *cursor) {
    char* start = std::strstr(buffer + *cursor, "S:{");
    if (start == nullptr) {
        std::cerr << "Format de données invalide : S:{ introuvable." << std::endl;
        return -1; // Valeur de temps invalide pour indiquer une erreur
    }
    *cursor = start - buffer + 3; 
    int day, month, year, seconds;
    if (std::sscanf(buffer + *cursor, "%d/%d/%d/%d}", &day, &month, &year, &seconds) != 4) {
        std::cerr << "Format de données invalide : Impossible de lire la date et l'heure." << std::endl;
        return -1; // Valeur de temps invalide pour indiquer une erreur
    }
    *cursor += std::strlen("jj/mm/aaaa/sssss}") + 1; // +1 pour passer le '}'

    // Construction de la structure tm pour la conversion en std::time_t
    std::tm timeinfo = {};
    timeinfo.tm_sec = seconds % 60;
    timeinfo.tm_min = seconds / 60 % 60;
    timeinfo.tm_hour = seconds / 3600;
    timeinfo.tm_mday = day;
    timeinfo.tm_mon = month - 1; // Les mois commencent à 0 dans struct tm
    timeinfo.tm_year = year - 1900; // Année moins 1900 dans struct tm
    timeinfo.tm_isdst = -1; // Indéterminé
    // Conversion de la structure tm en std::time_t
    std::time_t time = std::mktime(&timeinfo);
    if (time == -1) {
        std::cerr << "Erreur lors de la conversion de la date et de l'heure en std::time_t." << std::endl;
        return -1; // Valeur de temps invalide pour indiquer une erreur
    }

    return time;
}

int Message::translateFromBuffer(char *buffer, int bufferLength) {
    int cursor = 0;
    if( assertChar('{', buffer, cursor) == 1) {
        return -1;
    };
    cursor++;
    this->setMessageId(unpackInt(buffer, &cursor, 'I'));
    if( assertChar(',', buffer, cursor) == 1) {
        return -1;
    };
    cursor++;
    this->setIdAuteur( unpackInt(buffer, &cursor, 'A'));
    if( assertChar(',', buffer, cursor) == 1) {
        return -1;
    };
    cursor++;
    this->setIdAuteur( unpackInt(buffer, &cursor, 'D'));
    if( assertChar(',', buffer, cursor) == 1) {
        return -1;
    };
    cursor++;
    this->setHeureEnvoi( unpackTime(buffer, &cursor));
    cursor++;
    this->setContenu( unpackString(buffer, &cursor, 'C'));
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