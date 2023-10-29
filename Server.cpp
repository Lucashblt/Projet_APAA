#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>

//constructeur par defaut
Server::Server() {
    nbrOfSensors = 0;
    consolActivation = false;
    logActivation = false; 
}

//constructeur par paramatre
Server::Server(int nbrOfSensors, bool consolActivation, bool logActivation) {
    this->nbrOfSensors = nbrOfSensors;
    this->consolActivation = consolActivation;
    this->logActivation = logActivation;
}

//constructeur par recopie
Server::Server(const Server& server) {
    nbrOfSensors = server.nbrOfSensors;
    consolActivation = server.consolActivation;
    logActivation = server.logActivation;
}

//destructeur
Server::~Server() {}


int Server::getNumberOfSensors() const {
    return nbrOfSensors;
}
void Server::incrementNumberOfSensors() {
    ++nbrOfSensors;
}

// Active la console
void Server::setConsolActivation(bool activateConsole) {
    consolActivation = activateConsole;
}
//Active l'ecriture dans le fichier 
void Server::setLogActivation(bool activateLog) {
    logActivation = activateLog;
}

//surcharge de l'operateur =
Server& Server::operator=(const Server& server) {
    if (this == &server) {
        return *this;
    }
    nbrOfSensors = server.nbrOfSensors;
    consolActivation = server.consolActivation;
    logActivation = server.logActivation;

    return *this;
}

// surcharge operateur <<
std::ostream& operator<<(std::ostream& os, const Server& server) {
    os << "Number of Sensors: " << server.nbrOfSensors << std::endl;
    os << "Console Activation: " << (server.consolActivation ? "Active" : "Inactive") << std::endl;
    os << "Log Activation: " << (server.logActivation ? "Active" : "Inactive") << std::endl;
    return os;
}


// function de reception des données
template <typename T>
void Server::dataRcv(const std::string& sensorName, T dataSens) {
    if (consolActivation) {
        consoleWrite(sensorName, dataSens);
    }
    if (logActivation) {
        fileWrite(sensorName, dataSens);
    }
}

// Ecrit dans la console pour les capteurs temperature, humidite et sons
template <typename T>
void Server::consoleWrite(const std::string& sensorName, T dataSens) {
    std::stringstream output;
    output << "Sensor " << sensorName << " data : " << dataSens;
    std::cout << output.str() << std::endl;
}

// Ecrit dans la console pour le capteur lumière
template <>
void Server::consoleWrite<bool>(const std::string& sensorName, bool dataSens) {
    std::stringstream output;
    output << "Sensor " << sensorName << " is " << (dataSens ? "On" : "Off");
    std::cout << output.str() << std::endl;
}

// avoir l'heure et la date actuelle
std::string currentDateTime() {
	std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);
	char buffer[128];
	strftime(buffer, sizeof(buffer), "%m-%d-%Y %X", now);
	return buffer;
}
// Ecrit dans le fichier les valeurs des capteurs (chaque capteur a son propre fichier)
template <typename T>
void Server::fileWrite(const std::string& sensorName, T dataSens) {
    // Utilise le nom du capteur pour créer un nom de fichier unique
    std::string fileName = "server_log_" + sensorName + ".txt";  
    std::ofstream Myfile(fileName, std::ios::app);
    if (!Myfile.is_open()) {
        std::cout << "failed to open" << std::endl;
    } else {
        Myfile << currentDateTime();
        if(sensorName == "light"){
            Myfile << " : Sensor "<< sensorName <<" is " << (dataSens ? "On" : "Off") << std::endl;
        }else {
            Myfile << " : Sensor "<< sensorName <<" data : " << dataSens << std::endl;
        }
        Myfile.close();
    }
}

// Instanciations explicites pour les types de données supportés
template void Server::dataRcv<float>(const std::string& sensorName, float dataSens);
template void Server::dataRcv<bool>(const std::string& sensorName, bool dataSens);
template void Server::dataRcv<int>(const std::string& sensorName, int dataSens);