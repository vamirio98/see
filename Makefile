SRC = main.cpp Engine.cpp Logger.cpp
CC = g++
COMPILER_FLAGS = -Wall
LINKER_FLAGS = -lSDL2 -lSDL2_image
TARGET = see

build: $(SRC)
	$(CC) $(SRC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(TARGET)

run:
	./$(TARGET)
