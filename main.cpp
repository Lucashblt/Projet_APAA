#include <iostream>
#include <thread>  
#include <mutex>
#include "Server.hpp"
#include "Sensor.hpp"
#include "Scheduler.hpp"

Server server;

    
// Création des planificateurs (Schedulers) pour les différents types de capteurs
Scheduler<float> schedulerFloat(&server);
Scheduler<float> schedulerFloat2(&server);
Scheduler<bool> schedulerBool(&server);
Scheduler<int> schedulerInt(&server);


int main() {
    //initialisation du generateur de nombre aleatoire
    srand(time(nullptr));

    //Cree d'un objet server
    server.setConsolActivation(true); // Active la console
    server.setLogActivation(true); //Active le fichier
    
    //Creation des capteurs de temperature, humidite, lumiere et sons
    std::cout << "Creating sensor" << std::endl;
    Sensor<float> temperatureSensor;
    temperatureSensor.setServer(&server);
    Sensor<float> humiditySensor;
    humiditySensor.setServer(&server);
    Sensor<bool> lightSensor;
    lightSensor.setServer(&server);
    Sensor<int> soundSensor;
    soundSensor.setServer(&server);

    // Demandez à l'utilisateur les intervalles pour chaque capteur
    int intervalTemperature;
    int intervalHumidity;
    int intervalLight;
    int intervalSound;

    std::cout << "Entrez l'intervalle en secondes pour le capteur de temperature : ";
    std::cin >> intervalTemperature;
    std::cout << "Entrez l'intervalle en secondes pour le capteur d'humidite : ";
    std::cin >> intervalHumidity;
    std::cout << "Entrez l'intervalle en secondes pour le capteur de lumiere : ";
    std::cin >> intervalLight;
    std::cout << "Entrez l'intervalle en secondes pour le capteur de son : ";
    std::cin >> intervalSound;


    // Ajoute les capteurs avec leurs intervalles et declaration des noms des capteurs
    std::cout << "Adding sensor to scheduler" << std::endl;
    schedulerFloat.addSensor(&temperatureSensor, std::chrono::seconds(intervalTemperature));
    schedulerFloat.setSensorName(&temperatureSensor, "temperature");
    schedulerFloat2.addSensor(&humiditySensor, std::chrono::seconds(intervalHumidity));
    schedulerFloat2.setSensorName(&humiditySensor, "humidity");
    schedulerBool.addSensor(&lightSensor, std::chrono::seconds(intervalLight));
    schedulerBool.setSensorName(&lightSensor, "light");
    schedulerInt.addSensor(&soundSensor, std::chrono::seconds(intervalSound));
    schedulerInt.setSensorName(&soundSensor, "sound");
    
    // Lancement des planificateurs dans des threads séparés
    std::thread t1([]() {
        schedulerFloat2.startScheduling();
	});
    std::thread t2([]() {
        schedulerFloat.startScheduling();
	});
    std::thread t3([]() {
		schedulerBool.startScheduling();
	});
    
    /*
    // Attendez que tous les threads aient démarré
    t1.join();
    t2.join();
    t3.join();
    */
    // Lance le planificateur pour le capteur sound
    schedulerInt.startScheduling();
   
    return 0;
}

