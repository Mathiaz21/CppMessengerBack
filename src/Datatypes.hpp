#include <string>
#include <ctime>
#include <iostream>

#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

class Message {

    private:
        // Variables 
        std::string idMessage;
        int idAuteur;
        int idDestinataire;
        std::string contenu;
        int reaction;
        std::time_t heureEnvoi;
        std::time_t heureReception;
        std::time_t heureLecture;

    public:
        // Getters
        std::string getIdMessage();
        int getIdAuteur();
        int getIdDestinataire();
        std::string getContenu();
        int getReaction();
        std::time_t getHeureEnvoi();
        std::time_t getHeureReception();
        std::time_t getHeureLecture();
        

        // Setters
        void setIdMessage(std::string newId);
        void setIdAuteur(int newId);
        void setIdDestinataire(int newId);
        void setContenu(std::string newContenu);
        void setReaction(int newReaction);
        void setHeureEnvoi(std::time_t newHeureEnvoi);
        void setHeureReception(std::time_t newHeureReception);
        void setHeureLecture(std::time_t newHeureLecture);

        //Debugging
        void printMessage();

        // Utilities
        void copyMessage(Message newMessage);


        // Constructors
        Message();
        Message(std::string theIdMessage, int theIdAuteur, int theIdDestinataire);
        Message(std::string theIdMessage, int theIdAuteur, int theIdDestinataire, std::string theContenu);
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

        // Utilities
        void copyUser(User newUser);

        // Constructors
        User();
        User(int theUserId, std::string thePseudo, std::string thePassword);

        // Destructor
        ~User();

};


#endif //DATA_TYPES_HPP