CC=g++
STD=-std=c++17
CFLAGS=-Wall
INC_PATH=-I"./libs/"
SRC=$(shell find src -name '*.cpp')
OBJ=$(patsubst src/%.cpp, build/%.o, $(SRC))
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3
EXEC=bin/exec

all: $(EXEC)

$(EXEC): $(OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(STD) $(INC_PATH) $(OBJ) $(LFLAGS) -o $(EXEC)

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)  # Crea el directorio necesario para el archivo objeto
	$(CC) $(CFLAGS) $(STD) $(INC_PATH) -c $< -o $@

clean:
	rm -rf bin build

run: all
	./$(EXEC)
