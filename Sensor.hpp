#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Server.hpp"

template <typename T>
class Sensor {
    private:
        T valSense;
        class Server* server;

    public:
        Sensor();
        Sensor(T valRcv);
        Sensor(const Sensor& sensor);
        ~Sensor();

        T generateData();
        void readData();
        T sendData();
        void setServer(class Server* server);
};

#endif  
