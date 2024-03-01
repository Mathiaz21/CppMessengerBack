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
        int getIdMessage();
        int getIdAuteur();
        int getIdDestinataire();
        std::string getContenu();
        int getReaction();
        std::time_t getHeureEnvoi();
        std::time_t getHeureReception();
        std::time_t getHeureLecture();
        

        // Setters
        void setIdMessage(int newId);
        void setIdAuteur(int newId);
        void setIdDestinataire(int newId);
        void setContenu(std::string newContenu);
        void setReaction(int newReaction);
        void setHeureEnvoi(std::time_t newHeureEnvoi);
        void setHeureReception(std::time_t newHeureReception);
        void setHeureLecture(std::time_t newHeureLecture);

        //Debugging
        void printMessage();

    // Constructors
    Message(int theIdMessage, int theIdAuteur, int theIdDestinataire);
    Message(int theIdMessage, int theIdAuteur, int theIdDestinataire, std::string theContenu);
    Message(int theIdAuteur, int theIdDestinataire, std::string theContenu);

    // Destructor
    ~Message();

};

class User {

    private:

        // Variables
        int userId;
        std::string pseudo;
        std::string password;
    
    public:

        // Getters
        int getId();
        std::string getPseudo();
        std::string getPassword();
        bool testPassword(std::string testPassword);

        // Setters
        void setId(int theId);
        void setPseudo(std::string thePseudo);
        void setPassword(std::string thePassword);

        User(int theUserId, std::string thePseudo, std::string thePassword);

        ~User();

};


#endif //DATA_TYPES_HPP