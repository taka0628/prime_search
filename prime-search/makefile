CXX = g++

TARGET = main.out

# SRCS = $(shell find . -name "*.cpp" -type f | cut -d '/' -f 2)
SRCS = main.cpp traceback.cpp

OBJ_DIR = build

OBJS = ${SRCS:%.cpp=${OBJ_DIR}/%.o}

LDGFLAGS = -lpthread

LDFLAGS = -pthread

CFLAGS = -Wall\
	-std=c++11\
	-O2


all:
	make ${TARGET}

${TARGET}: ${OBJS}
	${CXX} -o $@ $^ ${LDFLAGS} ${LDGFLAGS}

${OBJ_DIR}/%.o: %.cpp
	mkdir -p build
	cd build;\
	${CXX} -c ../$^ ${CFLAGS}

benchmark:
	make run -C benchmark

run: ${TARGET}
	./${TARGET}

test: ${TARGET}
	./${TARGET} 2

clean:
	rm -rf ${OBJDIR}/*.o ${TARGET}
	rm -rf $(shell find . -name *.out -type f)

debug:
	make clean
	make "CFLAGS = ${CFLAGS} -g -O0"

rebuild:
	make clean
	make