CC=/usr/bin/g++
SRC_DIR=src
INCLUDE_DIR=include
BUILD_DIR=build
OBJ_DIR=obj
COMPILE_OPT=-O2 -std=c++17 -Wall \
	-Werror -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function \
	-I$(INCLUDE_DIR)
BUILD_OPT=-g -lstdc++ -lm -static
DEPS=-lproperties

all: $(OBJ_DIR) $(BUILD_DIR) server

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

main.o: $(SRC_DIR)/main.cpp
	$(CC) $(COMPILE_OPT) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

server.o: $(SRC_DIR)/server.cpp
	$(CC) $(COMPILE_OPT) -c $(SRC_DIR)/server.cpp -o $(OBJ_DIR)/server.o

request.o: $(SRC_DIR)/request.cpp
	$(CC) $(COMPILE_OPT) -c $(SRC_DIR)/request.cpp -o $(OBJ_DIR)/request.o

response.o: $(SRC_DIR)/response.cpp
	$(CC) $(COMPILE_OPT) -c $(SRC_DIR)/response.cpp -o $(OBJ_DIR)/response.o

lib.o: $(SRC_DIR)/lib.cpp
	$(CC) $(COMPILE_OPT) -c $(SRC_DIR)/lib.cpp -o $(OBJ_DIR)/lib.o

server: main.o server.o request.o response.o lib.o
	$(CC) $(BUILD_OPT) $(OBJ_DIR)/main.o $(OBJ_DIR)/server.o \
		$(OBJ_DIR)/request.o $(OBJ_DIR)/response.o $(OBJ_DIR)/lib.o \
		-o $(BUILD_DIR)/server

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)
