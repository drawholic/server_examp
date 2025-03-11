CXX = g++
CXX_FLAGS = -I include

SRC_DIR = src

BUILD_DIR = build
 
all: ${BUILD_DIR} ${BUILD_DIR}/client_main ${BUILD_DIR}/server_main

${BUILD_DIR}:
	mkdir -p $@

${BUILD_DIR}/client_main: ${SRC_DIR}/client_main.cpp ${BUILD_DIR}/Client.o
	${CXX} ${CXX_FLAGS} $^ -o $@

${BUILD_DIR}/server_main: ${SRC_DIR}/server_main.cpp ${BUILD_DIR}/Server.o
	${CXX} ${CXX_FLAGS} $^ -o $@

${BUILD_DIR}/Server.o: ${SRC_DIR}/Server.cpp
	${CXX} ${CXX_FLAGS} -c $^ -o $@

${BUILD_DIR}/Client.o: ${SRC_DIR}/Client.cpp
	${CXX} ${CXX_FLAGS} -c $^ -o $@