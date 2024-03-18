#include "CommFront.hpp"



/*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

* * * * * * * * * * * * * SOCKET HANDLER  * * * * * * * * * * * * * * *

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */




// Utilities

void SocketHandler::recvNSave(){
  // Envoyer un message de réponse au client
  // send(new_socket, "Hello, world!", 13, 0);
  this->nb_bytes = recv(new_socket, buffer, sizeof(buffer), 0);
  this->buffer[nb_bytes] = '\0';
  //std::cout << "Buffy : " << buffer << "\n";
}

std::time_t SocketHandler::stringToTime(const std::string& dateTimeStr) {
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

void SocketHandler::translateFromBuffer(const std::string& encodedMessage, Message *message) {
    size_t pos = encodedMessage.find("I:{");
    if (pos == std::string::npos)
        return; 
    size_t posEnd = encodedMessage.find("},", pos);
    if (posEnd == std::string::npos)
        return; 
    std::string messageIdStr = encodedMessage.substr(pos + 3, posEnd - pos - 3);
    message->setMessageId(std::stoi(messageIdStr));
    pos = encodedMessage.find("A:{");
    if (pos == std::string::npos)
        return;
    posEnd = encodedMessage.find("},", pos);
    if (posEnd == std::string::npos)
        return;
    std::string idAuteurStr = encodedMessage.substr(pos + 3, posEnd - pos - 3);
    message->setIdAuteur(std::stoi(idAuteurStr));
    // this->setUserId(std::stoi(idAuteurStr));
    pos = encodedMessage.find("D:{");
    if (pos == std::string::npos)
        return;
    posEnd = encodedMessage.find("},", pos);
    if (posEnd == std::string::npos)
        return;
    std::string idDestinataireStr = encodedMessage.substr(pos + 3, posEnd - pos - 3);
    message->setIdDestinataire(std::stoi(idDestinataireStr));
    pos = encodedMessage.find("S:{");
    if (pos == std::string::npos)
        return;
    posEnd = encodedMessage.find("},", pos);
    if (posEnd == std::string::npos)
        return;
    std::string heureEnvoiStr = encodedMessage.substr(pos + 3, posEnd - pos - 3);
    message->setHeureEnvoi(stringToTime(heureEnvoiStr));
    pos = encodedMessage.find("C:{");
    if (pos == std::string::npos)
        return;
    posEnd = encodedMessage.find("}}", pos);
    if (posEnd == std::string::npos)
        return;
    std::string contenuStr = encodedMessage.substr(pos + 3, posEnd - pos - 3);
    message->setContenu(contenuStr);


}


// Getters
char *SocketHandler::getBuffer(){ return this->buffer; };
int SocketHandler::getSocketUserId(){ return this->socketUserId; };


// Setterss
void SocketHandler::setUserId(int theUserId){ this->socketUserId = theUserId; };

// Constructor
SocketHandler::SocketHandler() {
  opt = 1;
  addrlen = sizeof(address);
  char buffer[1024] = {0};

  // Créer un socket
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    std::cerr << "Erreur lors de la création du socket" << std::endl;
  }

  // Configurer le socket pour réutiliser l'adresse et le port
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    std::cerr << "Erreur lors de la configuration du socket" << std::endl;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  // Associer le socket à une adresse et un port
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    std::cerr << "Erreur lors de la liaison du socket" << std::endl;
  }

  // Écouter les connexions entrantes
  if (listen(server_fd, 3) < 0) {
    std::cerr << "Erreur lors de l'écoute du socket" << std::endl;
  }

  // Accepter les connexions entrantes
  if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
    std::cerr << "Erreur lors de l'acceptation de la connexion" << std::endl;
  }
}

SocketHandler::~SocketHandler() {
  // Fermer les sockets
  close(server_fd);
  close(new_socket);
}