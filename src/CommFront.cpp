#include "CommFront.hpp"



/*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

* * * * * * * * * * * * * SOCKET HANDLER  * * * * * * * * * * * * * * *

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



void SocketHandler::sendHelloWorld(){
  // Envoyer un message de réponse au client
  send(new_socket, "Hello World!", 13, 0);
    char buffer2[1024];
  recv(new_socket, buffer2, sizeof(buffer2), 0 );
  std::cout << buffer2 << "\n";
}


SocketHandler::SocketHandler(int socketId) {
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
  address.sin_port = htons(8080 + socketId);

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


/*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

* * * * * * * * * * * * * FRONT COMMUNICATOR  * * * * * * * * * * * * *

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Utilities
int FrontCommunicator::socketisActive(int socketId) {
  unsigned int activeIndicator = 1;
  activeIndicator << socketId;
  if(activeIndicator && this->activeSockets) {
    return 1;
  }
  return 0;
}

void FrontCommunicator::sendHelloWorld(int socketId) {
  if( socketisActive(socketId) == 1){
    this->sockets[socketId].sendHelloWorld();
  } else {
    std::cerr << "Error : Socket no " << socketId << " is inactive !";
  }
}



int FrontCommunicator::activateSocket(int socketId){
  return 0;
};


// Constructor
FrontCommunicator::FrontCommunicator(int nbSockets) {
  unsigned int activeSocketbit = 1;
  for(int i; i < nbSockets; i++) {
    this->sockets[i] = SocketHandler(i);
    this->activeSockets += activeSocketbit;
    activeSocketbit *= 2;
  }
}


// Destructor
FrontCommunicator::~FrontCommunicator() {};