#include "Sensor.hpp"

//construceur par default
template <typename T>
Sensor<T>::Sensor() {
    valSense = T();
}
//construceur par parametre
template <typename T>
Sensor<T>::Sensor(T valRcv) {
    valSense = valRcv;
}
//construceur par copie
template <typename T>
Sensor<T>::Sensor(const Sensor& sensor) {
    valSense = sensor.valSense;
}
//destruceur
template <typename T>
Sensor<T>::~Sensor() {

}

template <typename T>
T Sensor<T>::generateData() {
    std::cout << "generateData: " << std::endl;
}

template<>
float Sensor<float>::generateData() {
    float val = ((rand()%1000)/17.0) +1;
    return val;
}

template<>
bool Sensor<bool>::generateData() {
    bool val = false;
    val = rand()%2;
    return val;
}

template<>
int Sensor<int>::generateData() {
    int val = 0;
    val = rand()%130;
    return val;
}


template <typename T>
void Sensor<T>::readData() {
    valSense = generateData();
}

template <typename T>
T Sensor<T>::sendData() {
    std::string sensorName = "sensorName";
    if (server != nullptr) {
        server->dataRcv(sensorName, valSense);
    }
    return valSense;
}

template <typename T>
void Sensor<T>::setServer(Server* server) {
    this->server = server;
}

template class Sensor<float>;
template class Sensor<bool>;
template class Sensor<int>;
