CC=g++
STD=-std=c++17
CFLAGS=-Wall -Wextra
INC_PATH=-I"./libs/"
SRC=$(shell find src -name '*.cpp')
OBJ=$(patsubst src/%.cpp, build/%.o, $(SRC))
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3 -ltinyxml2
EXEC=bin/exec

SANITIZERS=
ifeq ($(SAN),asan)
    SANITIZERS=-fsanitize=address
endif
ifeq ($(SAN),msan)
    SANITIZERS=-fsanitize=memory
endif
ifeq ($(SAN),tsan)
    SANITIZERS=-fsanitize=thread
endif
ifeq ($(SAN),ubsan)
    SANITIZERS=-fsanitize=undefined
endif

all: $(EXEC)

$(EXEC): $(OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(STD) $(INC_PATH) $(SANITIZERS) $(OBJ) $(LFLAGS) -o $(EXEC)

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(STD) $(INC_PATH) $(SANITIZERS) -c $< -o $@

clean:
	rm -rf bin build

run: all
	./$(EXEC)

run-d: CFLAGS += -DDEBUG_FLAG=true
run-d: all
	./$(EXEC)

# Sanitizers
asan: SAN=asan
asan: clean all
	./$(EXEC)

msan: SAN=msan
msan: clean all
	./$(EXEC)

tsan: SAN=tsan
tsan: clean all
	./$(EXEC)

ubsan: SAN=ubsan
ubsan: clean all
	./$(EXEC)

# Valgrind Memory Checks
memcheck: all
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(EXEC)

docs:
	doxygen Doxyfile

.PHONY: all clean run run-d asan msan tsan ubsan memcheck docs