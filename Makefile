# Compilateur C++
CXX = g++
# Options de compilation
CXXFLAGS = -std=c++11 -Wall
# Fichiers source
SRCS = main.cpp Server.cpp Sensor.cpp Scheduler.cpp
# Fichiers headers
HEADERS = Server.hpp Sensor.hpp Scheduler.hpp
# Noms des fichiers objets générés
OBJS = $(SRCS:.cpp=.o)
# Nom de l'exécutable
TARGET = mon_programme

.PHONY: all clean

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
