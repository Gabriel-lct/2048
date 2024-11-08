# Nom de l'exécutable final
TARGET = 2048

# Les fichiers sources
SRC = ./src/2048.cpp ./src/Display.cpp ./src/Utils.cpp ./src/Game.cpp

# Le compilateur et les options
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Règle pour compiler le programme
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Nettoyer les fichiers générés
clean:
	rm -f $(TARGET)
