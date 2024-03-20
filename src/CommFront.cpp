#include "CommFront.hpp"



/*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

* * * * * * * * * * * * * SOCKET HANDLER  * * * * * * * * * * * * * * *

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */




// Utilities

void SocketHandler::routeRequest(DbCommunicator dbCommunicator) {
  // Reception
  this->nb_bytes = recv(new_socket, buffer, sizeof(buffer), 0);
  this->buffer[nb_bytes] = '\0';

  // Ajout Message
  if(buffer[0] == '{') {
    std::cout << "Reception : " << buffer << "\n";
    Message message;
    std::string encodedMessage = this->getBuffer();
    translateFromBuffer(encodedMessage, &message);
    dbCommunicator.addMessage(message);
  }
  // Demande d'envoi des données
  if(buffer[0] == '('){
    std::cout << "Envoi : " << buffer << "\n";
    int userId1 = buffer[1] - '0';
    int userId2 = buffer[3] - '0';
    sendConversation(userId1, userId2, dbCommunicator);
  }
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

std::string SocketHandler::timeToString(std::time_t *time) {
  std::string timeStr;
  std::tm *timeInfo = std::localtime(time);
  timeStr += std::to_string(timeInfo->tm_mday) += "/";
  timeStr += std::to_string(timeInfo->tm_mon) += "/";
  timeStr += std::to_string(timeInfo->tm_year) += "/";

  int nbSeconds = timeInfo->tm_sec + 60*( timeInfo->tm_min + 60*( timeInfo->tm_hour ) );
  timeStr += std::to_string(nbSeconds);
  return timeStr;
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
    this->setUserId(std::stoi(idAuteurStr));
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


void SocketHandler::translateToBuffer(char *buffer, int *bufferLen, Message *message) {

  // Création de la chaine de caractères
  std::string messageStr = "{I:{" + std::to_string(message->getMessageId()) + "},";
  messageStr += "A:{" + std::to_string(message->getIdAuteur()) + "},";
  messageStr += "D:{" + std::to_string(message->getIdDestinataire()) + "},";
  std::time_t heureEnvoi = message->getHeureEnvoi();
  messageStr += "S:{" + timeToString(&heureEnvoi);
  messageStr += "C:{" + message->getContenu() + "}}\0";
  // Écriture des réponses dans les buffers
  *bufferLen = messageStr.length();
  for(int i = 0; i < *bufferLen; i++) {
    buffer[i] = messageStr[i];
  }
}

void SocketHandler::sendConversation(int userId1, int userId2, DbCommunicator dbCommunicator) {
  int convLength = dbCommunicator.queryConversationLength(userId1, userId2);
  Message *conversation = new Message[convLength];
  dbCommunicator.queryConversation(conversation, convLength, userId1, userId2);
  for(int i = 0; i < convLength; i++) {
    char buffer[1024];
    int bufferLen;
    translateToBuffer(buffer, &bufferLen, conversation+i);
    std::cout << "Buffer : " << buffer <<"\n";
    send(new_socket, buffer, bufferLen, 0);
  }
}


// Getters
char *SocketHandler::getBuffer(){ return this->buffer; };
int SocketHandler::getSocketUserId(){ return this->socketUserId; };
int SocketHandler::getNbBytes(){ return this->nb_bytes; };

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