#include <iostream>
#include "Server.hpp"
#include "Sensor.hpp"
#include "Scheduler.hpp"

int main() {
    srand(time(nullptr));

    Server server;
    server.setConsolActivation(true); // Enable console output
    server.setLogActivation(true); // Enable log output
    

    std::cout << "Creating temperature sensor" << std::endl;
    Sensor<float> temperatureSensor;
    temperatureSensor.setServer(&server);

    Scheduler<float> schedulerFloat(&server);

    std::cout << "Adding temperature to scheduler" << std::endl;
    schedulerFloat.addSensor(&temperatureSensor, std::chrono::seconds(1));
    schedulerFloat.setSensorName(&temperatureSensor, "temperature");

    
    std::cout << "Creating humidity sensor" << std::endl;
    Sensor<float> humiditySensor;
    humiditySensor.setServer(&server);

    //Scheduler<float> schedulerFloat(&server);

    std::cout << "Adding humidity to scheduler" << std::endl;
    schedulerFloat.addSensor(&humiditySensor, std::chrono::seconds(2));
    schedulerFloat.setSensorName(&humiditySensor, "humidity");
    
    /*
    std::cout << "Creating light sensor" << std::endl;
    Sensor<bool> lightSensor;
    lightSensor.setServer(&server);

    Scheduler<bool> schedulerBool(&server);

    std::cout << "Adding light to scheduler" << std::endl;
    schedulerBool.addSensor(&lightSensor, std::chrono::seconds(3));
    schedulerBool.setSensorName(&lightSensor, "light");
    

    std::cout << "Creating sound sensor" << std::endl;
    Sensor<int> soundSensor;
    soundSensor.setServer(&server);

    Scheduler<int> schedulerInt(&server);

    std::cout << "Adding sound to scheduler" << std::endl;
    schedulerInt.addSensor(&soundSensor, std::chrono::seconds(4));
    schedulerInt.setSensorName(&soundSensor, "sound");
    */
    std::cout << "Starting scheduling float" << std::endl;
    schedulerFloat.startScheduling();
    //ne vient pas ici ?
    /*
    std::cout << "Starting scheduling bool" << std::endl;
    schedulerBool.startScheduling();
    std::cout << "Starting scheduling int" << std::endl;
    schedulerInt.startScheduling();
    */
    return 0;
}

/*
int main(){
    srand(time(nullptr));

    Server server;
    server.setConsolActivation(true); // Enable console output
    server.setLogActivation(true); // Enable log output

    std::vector<Sensor<float>*> sensors;

    std::cout << "Creating temperature sensor" << std::endl;
    Sensor<float>* temperatureSensor = new Sensor<float>();
    temperatureSensor->setServer(&server);
    sensors.push_back(temperatureSensor);

    // autre capteur
    Scheduler<float> schedulerFloat(&server);

    std::cout << "Starting Scheduling float" << std::endl;
    schedulerFloat.startScheduling();

    // Nettoyez les capteurs à la fin du programme
    for (Sensor<float>* sensor : sensors) {
        delete sensor;
    }

    return 0;

}*/