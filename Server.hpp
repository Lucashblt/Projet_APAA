#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

template <typename T>
class Sensor;  // Forward declaration of Sensor class

class Server {
public:
    Server();
    Server(int nbrOfSensors, bool consolActivation, bool logActivation);
    Server(const Server& server);
    ~Server();

    Server& operator=(const Server& server);

    void setConsolActivation(bool activateConsole);
    void setLogActivation(bool activateLog);
    /*
    std::ostream& operator<<(std::ostream& os, int dataSens);
    std::ostream& operator<<(std::ostream& os, float dataSens_toString);
    */
    template <typename T>
    void dataRcv(const std::string& sensorName, T dataSens);
        

private:
    int nbrOfSensors;
    bool consolActivation;
    bool logActivation;

    template <typename T>
    void consoleWrite(const std::string& sensorName, T dataSens);
    template <typename T>
    void fileWrite(const std::string& sensorName, T dataSens);

};

#endif
