#include "Scheduler.hpp"
#include <chrono>
#include <thread>
#include <vector>

template <typename T>
Scheduler<T>::Scheduler(Server* server) : server(server) {}

template <typename T>
Scheduler<T>::~Scheduler() {
    for (Sensor<T>* sensor : sensors) {
        delete sensor;
    }
}

template <typename T>
void Scheduler<T>::addSensor(Sensor<T>* sensor, std::chrono::milliseconds interval) {
    sensors.push_back(sensor);
    intervals.push_back(interval);
}

template <typename T>
void Scheduler<T>::setSensorName(Sensor<T>* sensor, const std::string& name) {
    sensors.push_back(sensor);
    sensorNames.push_back(name);
}

template <typename T>
void Scheduler<T>::startScheduling() {
    while (true) {
        std::cout << "debug startscheduling 0" << std::endl;
        for (size_t i = 0; i < sensors.size(); ++i) {
            Sensor<T>* sensor = sensors[i];
            std::chrono::milliseconds interval = intervals[i];
            std::string name = sensorNames[i];
            
            sensor->readData();
            T data = sensor->sendData();
            if (server != nullptr) {
                server->dataRcv(name, data);
            }
            std::cout << "debug startscheduling 1" << std::endl;
            std::this_thread::sleep_for(interval);
            std::cout << "debug startscheduling 2" << std::endl;
        }
        std::cout << "debug startscheduling 3" << std::endl;
    }
}

// Explicit instantiations for the supported data types
template class Scheduler<float>;
template class Scheduler<bool>;
template class Scheduler<int>;
