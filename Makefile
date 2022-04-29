CC=/usr/bin/g++
BUILD_DIR=build
OBJ_DIR=obj
COMPILE_OPT=-O2 -std=c++17 -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
BUILD_OPT=-g -lstdc++ -lm -static

all: server

main.o: main.cpp
	$(CC) $(COMPILE_OPT) -c main.cpp -o $(OBJ_DIR)/main.o

server.o: server.cpp
	$(CC) $(COMPILE_OPT) -c server.cpp -o $(OBJ_DIR)/server.o

request.o: request.cpp
	$(CC) $(COMPILE_OPT) -c request.cpp -o $(OBJ_DIR)/request.o

response.o: response.cpp
	$(CC) $(COMPILE_OPT) -c response.cpp -o $(OBJ_DIR)/response.o

lib.o: lib.cpp
	$(CC) $(COMPILE_OPT) -c lib.cpp -o $(OBJ_DIR)/lib.o

server: main.o server.o request.o response.o lib.o
	$(CC) $(BUILD_OPT) $(OBJ_DIR)/main.o $(OBJ_DIR)/server.o $(OBJ_DIR)/request.o $(OBJ_DIR)/response.o $(OBJ_DIR)/lib.o -o $(BUILD_DIR)/server