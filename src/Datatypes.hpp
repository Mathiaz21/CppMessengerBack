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

    // Destructor
    ~Message();

};


#endif //DATA_TYPES_HPP