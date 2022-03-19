CXX = g++

TARGET = main.out

SRCS = $(shell find . -name *.cpp -type f)

OBJ_DIR = build

OBJS = ${SRCS:%.cpp=${OBJ_DIR}/%.o}

LDGFLAGS = -lpthread

LDFLAGS = -pthread

CFLAGS = -Wall\
	-std=c++11

all:
	make ${TARGET} -j$(shell nproc)

${TARGET}: ${OBJS}
	${CXX} -o $@ $^ ${LDFLAGS} ${LDGFLAGS}

${OBJS}: *.cpp
	mkdir -p build
	cd build;\
	${CXX} -c ../$^ ${CFLAGS}

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