CXX = g++
CXX_FLAGS = -I include


SRC_DIR = src

BUILD_DIR = build
 
all: ${BUILD_DIR} ${BUILD_DIR}/main 

${BUILD_DIR}:
	mkdir -p $@

${BUILD_DIR}/server_main: ${SRC_DIR}/server_main.cpp ${OBJS}
	${CXX} ${CXX_FLAGS} $^ -o $@

${BUILD_DIR}/client_main: ${SRC_DIR}/client_main.cpp ${OBJS}
	${CXX} ${CXX_FLAGS} $^ -o $@ 
