#include "Scheduler.hpp"
#include <chrono>
#include <thread>
#include <vector>

template <typename T>
Scheduler<T>::Scheduler(Server* server) : server(server) {}

template <typename T>
Scheduler<T>::~Scheduler() {
    /*
    for (Sensor<T>* sensor : sensors) {
        delete sensor;
    }
    */
}

template <typename T>
void Scheduler<T>::addSensor(Sensor<T>* sensor, std::chrono::milliseconds interval) {
    sensors.push_back(sensor);
    intervals.push_back(interval);
}

template <typename T>
void Scheduler<T>::setSensorName(Sensor<T>* sensor, const std::string& name) {
    
    sensorNames.push_back(name);
}

template <typename T>
void Scheduler<T>::startScheduling() {
    for (size_t i = 0; i < sensors.size(); ++i) {
        Sensor<T>* sensor = sensors[i];
        std::chrono::milliseconds interval = intervals[i];
        std::string name = sensorNames[i];

        sensor->readData();
        T data = sensor->sendData();

        if (server != nullptr) {
            server->dataRcv(name, data);
        }

        std::this_thread::sleep_for(interval);
    }
} 

// Explicit instantiations for the supported data types
template class Scheduler<float>;
template class Scheduler<bool>;
template class Scheduler<int>;
