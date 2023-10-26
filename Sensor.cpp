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
Sensor<T>::~Sensor() {}

// Génère des données
template <typename T>
T Sensor<T>::generateData() {
    std::cout << "generateData: " << std::endl;
}
// genere les valeurs float pour les capteurs temperature et humidite
template<>
float Sensor<float>::generateData() {
    float val = ((rand()%1000)/17.0) +1;
    return val;
}
//genere la valeur booleen pour le capteur de lumiere
template<>
bool Sensor<bool>::generateData() {
    bool val = false;
    val = rand()%2;
    return val;
}
//genere la valeur int pour le capteur de son
template<>
int Sensor<int>::generateData() {
    int val = 0;
    val = rand()%130;
    return val;
}
// lit la valeur generée
template <typename T>
void Sensor<T>::readData() {
    valSense = generateData();
}
// Renvoie la valeur generée
template <typename T>
T Sensor<T>::sendData() {
    return valSense;
}
// Assigne un serveur au capteur
template <typename T>
void Sensor<T>::setServer(Server* server) {
    this->server = server;
}

// Instanciations explicites pour les types de données supportés
template class Sensor<float>;
template class Sensor<bool>;
template class Sensor<int>;
