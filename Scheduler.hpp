#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include "Sensor.hpp"
#include "Server.hpp"
#include <chrono>
#include <vector>

class Server;  // Forward declaration of Server class

template <typename T>
class Sensor;  // Forward declaration of Sensor class

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
    std::vector<Sensor<T>*> sensors; // Use std::vector<Sensor<T>*> for storing sensors
    std::vector<std::chrono::milliseconds> intervals;
    std::vector<std::string> sensorNames; // Store the sensor names
};

#endif
