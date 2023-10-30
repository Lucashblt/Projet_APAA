#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

template <typename T>
class Sensor;  // Forward declaration of Sensor class

class Server {
    private:
        int nbrOfSensors;
        bool consolActivation;
        bool logActivation;
        

    public:
        Server();
        Server(int nbrOfSensors, bool consolActivation, bool logActivation);
        Server(const Server& server);
        ~Server();

        int getNumberOfSensors() const;
        void incrementNumberOfSensors();

        Server& operator=(const Server& server);

        friend std::ostream& operator<<(std::ostream& os, const Server& server);

        void setConsolActivation(bool activateConsole);
        void setLogActivation(bool activateLog);
        
        template <typename T>
        void dataRcv(const std::string& sensorName, T dataSens);

        template <typename T>
        void consoleWrite(const std::string& sensorName, T dataSens);
        template <typename T>
        void fileWrite(const std::string& sensorName, T dataSens);

};

#endif
