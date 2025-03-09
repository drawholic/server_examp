CXX = g++
CXX_FLAGS = -I include


SRC_DIR = src

BUILD_DIR = build

OBJS = 


all: ${BUILD_DIR} ${BUILD_DIR}/main 

${BUILD_DIR}:
	mkdir -p $@

${BUILD_DIR}/main: ${SRC_DIR}/main.cpp ${OBJS}
	${CXX} ${CXX_FLAGS} $^ -o $@


