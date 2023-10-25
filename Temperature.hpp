#ifndef TEMPERATURE_HPP
#define TEMPERATURE_HPP

#include "Sensor.hpp"
#include <fstream>

class Temperature : public Sensor
{
    private:
        float temperature;
    public :
        Temperature();
        Temperature(float valRcv);
        void readData() override;
        void displayData() override;
        void writeToLogFile(std::ofstream& logFile) override;
};
#endif //TEMPERATURE_HPP