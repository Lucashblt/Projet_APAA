#include <iostream>
#include "Server.hpp"
#include "Sensor.hpp"
#include "Scheduler.hpp"

int main() {
    srand(time(nullptr));

    Server server;
    server.setConsolActivation(true); // Enable console output
    server.setLogActivation(true); // Enable log output
    

    std::cout << "Creating sensor" << std::endl;
    Sensor<float> temperatureSensor;
    temperatureSensor.setServer(&server);
    Sensor<float> humiditySensor;
    humiditySensor.setServer(&server);
    Sensor<bool> lightSensor;
    lightSensor.setServer(&server);
    Sensor<int> soundSensor;
    soundSensor.setServer(&server);

    Scheduler<float> schedulerFloat(&server);
    Scheduler<bool> schedulerBool(&server);
    Scheduler<int> schedulerInt(&server);

    std::cout << "Adding sensor to scheduler" << std::endl;
    schedulerFloat.addSensor(&temperatureSensor, std::chrono::seconds(1));
    schedulerFloat.setSensorName(&temperatureSensor, "temperature");
    schedulerFloat.addSensor(&humiditySensor, std::chrono::seconds(2));
    schedulerFloat.setSensorName(&humiditySensor, "humidity");
    schedulerBool.addSensor(&lightSensor, std::chrono::seconds(3));
    schedulerBool.setSensorName(&lightSensor, "light");
    schedulerInt.addSensor(&soundSensor, std::chrono::seconds(4));
    schedulerInt.setSensorName(&soundSensor, "sound");
    
    while(true){
        std::cout << "Starting scheduling float" << std::endl;
        schedulerFloat.startScheduling();
        
        std::cout << "Starting scheduling bool" << std::endl;
        schedulerBool.startScheduling();

        std::cout << "Starting scheduling int" << std::endl;
        schedulerInt.startScheduling();
    }
    return 0;
}

