#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


class FrontCommunicator {
    
    private:
        int server_fd, new_socket;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        char buffer[1024] = {0};

    public:
        FrontCommunicator();

}

int main() {
  int server_fd, new_socket;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  char buffer[1024] = {0};

  // Créer un socket
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    std::cerr << "Erreur lors de la création du socket" << std::endl;
    return 1;
  }

  // Configurer le socket pour réutiliser l'adresse et le port
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    std::cerr << "Erreur lors de la configuration du socket" << std::endl;
    return 1;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  // Associer le socket à une adresse et un port
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    std::cerr << "Erreur lors de la liaison du socket" << std::endl;
    return 1;
  }

  // Écouter les connexions entrantes
  if (listen(server_fd, 3) < 0) {
    std::cerr << "Erreur lors de l'écoute du socket" << std::endl;
    return 1;
  }

  // Accepter les connexions entrantes
  if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
    std::cerr << "Erreur lors de l'acceptation de la connexion" << std::endl;
    return 1;
  }

  // Envoyer un message de réponse au client
  send(new_socket, "Hello World!", 13, 0);
    char buffer2[1024];
  recv(new_socket, buffer2, sizeof(buffer2), 0 );
  std::cout << buffer2 << "\n";
  

  // Fermer les sockets
  close(server_fd);
  close(new_socket);

  return 0;
}
