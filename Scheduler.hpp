#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include "Sensor.hpp"
#include "Server.hpp"
#include <chrono>
#include <vector>

class Server;  

template <typename T>
class Sensor;  

template <typename T>
class Scheduler {
public:
    Scheduler(Server* server);
    ~Scheduler();

    void addSensor(Sensor<T>* sensor, std::chrono::milliseconds interval);
    void setSensorName(Sensor<T>* sensor, const std::string& name);
    void startScheduling();

private:
    Server* server;
    std::vector<Sensor<T>*> sensors;
    std::vector<std::chrono::milliseconds> intervals;
    std::vector<std::string> sensorNames; 
};

#endif
