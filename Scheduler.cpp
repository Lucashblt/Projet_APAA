#include "Scheduler.hpp"
#include <chrono>
#include <thread>
#include <vector>

//constructeur par recopie
template <typename T>
Scheduler<T>::Scheduler(Server* server) : server(server) {}

//Destructeur
template <typename T>
Scheduler<T>::~Scheduler() {
    // Pour chaque capteur dans le vecteur, libérer la mémoire (détruire le capteur)
    for (Sensor<T>* sensor : sensors) {
         delete sensor; 
    }
}

// Fonction d'ajout de capteur avec leur intervalle
template <typename T>
void Scheduler<T>::addSensor(Sensor<T>* sensor, std::chrono::milliseconds interval) {
    sensors.push_back(sensor);
    intervals.push_back(interval);
}

// Definition du nom du capteur
template <typename T>
void Scheduler<T>::setSensorName(Sensor<T>* sensor, const std::string& name) {
    sensorNames.push_back(name);
}

// Fonction de démarrage de la planification
template <typename T>
void Scheduler<T>::startScheduling() {
    while(true){
        for (size_t i = 0; i < sensors.size(); ++i) {
            Sensor<T>* sensor = sensors[i];
            std::chrono::milliseconds interval = intervals[i];
            std::string name = sensorNames[i];

            // Appele le capteur pour lire sa valeur
            sensor->readData();

            // recois la valeur lue depuis le capteur
            T data = sensor->sendData();

            // Envoie la valeur au serveur pour affichage dans la console et écriture dans un fichier
            if (server != nullptr) {
                server->dataRcv(name, data);
            }
            // Attente pour le prochain relevé du capteur en fonction de l'intervalle
            std::this_thread::sleep_for(interval);
        }
    }
} 



// Instanciations explicites pour les types de données supportés
template class Scheduler<float>;
template class Scheduler<bool>;
template class Scheduler<int>;
