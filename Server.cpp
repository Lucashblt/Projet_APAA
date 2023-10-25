#include "Server.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

Server::Server() {
    nbrOfSensors = 0;
    consolActivation = true;
    logActivation = true; 
}

Server::Server(int nbrOfSensors, bool consolActivation, bool logActivation) {
    this->nbrOfSensors = nbrOfSensors;
    this->consolActivation = consolActivation;
    this->logActivation = logActivation;
}
Server::Server(const Server& server) {
    nbrOfSensors = server.nbrOfSensors;
    consolActivation = server.consolActivation;
    logActivation = server.logActivation;
}

Server::~Server() {}

void Server::setConsolActivation(bool activateConsole) {
    consolActivation = activateConsole;
}

void Server::setLogActivation(bool activateLog) {
    logActivation = activateLog;
}
Server& Server::operator=(const Server& server) {
    if (this == &server) {
        return *this; // Avoid self-assignment
    }
    nbrOfSensors = server.nbrOfSensors;
    consolActivation = server.consolActivation;
    logActivation = server.logActivation;

    return *this;
}

// surcharge operateur <<

template <typename T>
void Server::dataRcv(const std::string& sensorName, T dataSens) {
    if (consolActivation) {
        consoleWrite(sensorName, dataSens);
    }
    if (logActivation) {
        fileWrite(sensorName, dataSens);
    }
}
// float et int 
template <typename T>
void Server::consoleWrite(const std::string& sensorName, T dataSens) {
    std::cout << "Sensor "<< sensorName <<  ", Data: " << dataSens << std::endl;
}

template <>
void Server::consoleWrite<bool>(const std::string& sensorName, bool dataSens) {
    std::cout <<"Light is " << (dataSens ? "On" : "Off") << std::endl;
}

template <typename T>
void Server::fileWrite(const std::string& sensorName, T dataSens) {
    std::ofstream Myfile("server_log.txt", std::ios::app);
    if (!Myfile.is_open()) {
        std::cout << "failed to open" << std::endl;
    } else {
        time_t currentTime = time(nullptr);
        Myfile << "Sensor "<< sensorName <<" Data: " << dataSens << " at " << ctime(&currentTime);
        Myfile.close();
    }
}

// Explicit instantiations for the supported data types
template void Server::dataRcv<float>(const std::string& sensorName, float dataSens);
template void Server::dataRcv<bool>(const std::string& sensorName, bool dataSens);
template void Server::dataRcv<int>(const std::string& sensorName, int dataSens);


/*

std::ostream& operator<<(std::ostream& os, int dataSens) {
    os << "Sensor Data: " << std::to_string(dataSens) << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, float dataSens_toString) {
    os << "Sensor Data: " << std::to_string(dataSens_toString) << std::endl;
    return os;
}

*/