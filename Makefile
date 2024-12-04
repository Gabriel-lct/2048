# Nom de l'exécutable final
TARGET = 2048

# Les fichiers sources
SRC = ./src/2048.cpp ./src/Display.cpp ./src/Utils.cpp ./src/Game.cpp ./src/AI.cpp ./src/GA.cpp ./src/GUI.cpp

# Le compilateur et les options
CXX = g++
CXXFLAGS = -std=c++17 -Wall -fopenmp # Include SDL2 headers
LDFLAGS = -lSDL2 -lSDL2_ttf # Link SDL2 and SDL2_ttf libraries

# Dossier de sortie
OUT_DIR = .

# Dossier contenant la police
FONT_DIR = ./fonts/ClearSans

# Règle pour compiler le programme
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/$(TARGET) $(SRC) $(LDFLAGS)
#	make copy-font

# Copier les fichiers de police dans le répertoire de sortie
#copy-font:
#	cp $(FONT_DIR)/*.ttf $(OUT_DIR)/

# Nettoyer les fichiers générés
#clean:
#	rm -f $(OUT_DIR)/$(TARGET)
#	rm -f $(OUT_DIR)/*.ttf
