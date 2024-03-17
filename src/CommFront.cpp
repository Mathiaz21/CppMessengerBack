#include "CommFront.hpp"



/*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

* * * * * * * * * * * * * SOCKET HANDLER  * * * * * * * * * * * * * * *

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


// Utilities
void SocketHandler::recvNPrint() {
  bytes_in_buffer = recv(front_socket, buffer, sizeof(buffer), 0);
  buffer[bytes_in_buffer] = '\0';
  if(bytes_in_buffer > 0){
    std::cout << buffer << "\n";
  }
}

void SocketHandler::initialiseClientSocket() {
  int client_socket = accept(main_socket, NULL, NULL);
  if (client_socket == -1) {
    std::cerr << "Erreur lors de l'acceptation de la connexion." << std::endl;
    close(main_socket);
  }
}

void SocketHandler::closeFrontSocket() {
  close(front_socket);
}


// Constructor
SocketHandler::SocketHandler() {
  if (main_socket == -1) {
  std::cerr << "Erreur lors de la création du socket." << std::endl;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080); // Port
  }

  if (bind(main_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
    std::cerr << "Erreur lors de la liaison du socket." << std::endl;
    close(main_socket);
  }

  if (listen(main_socket, 5) == -1) {
    std::cerr << "Erreur lors de l'écoute du socket." << std::endl;
    close(main_socket);
  }
}

SocketHandler::~SocketHandler() {
  // Fermer les sockets
  close(main_socket);
}