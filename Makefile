SRC = main.cpp Engine.cpp Logger.cpp File.cpp
CC = g++
COMPILER_FLAGS = -Wall
DEBUG_FLAGS = -g
LINKER_FLAGS = -lSDL2 -lSDL2_image
TARGET = see

build: $(SRC)
	$(CC) $(SRC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(TARGET)

debug: $(SRC)
	$(CC) $(SRC) $(COMPILER_FLAGS) $(DEBUG_FLAGS) $(LINKER_FLAGS) -o $(TARGET)

run:
	./$(TARGET)
