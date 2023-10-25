#include "Temperature.hpp"
#include <iostream>
#include <fstream>
#include <ctime>

// Constructeur par défaut
Temperature::Temperature() {
    temperature = 0.0; 
}
// Constructeur avec une valeur reçue
Temperature::Temperature(float valRcv) {
    temperature = valRcv;
}

void Temperature::readData() {
    // Générez une valeur aléatoire entre 0 et 30 °C.
    temperature = static_cast<float>(rand() % 31); 
    std::cout << "readData Temperature : " << temperature << std::endl;  
}


