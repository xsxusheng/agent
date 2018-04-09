##c/c++代码编译Makefile
###########################################################

TARGET = host
CFLAGS = -Wall -O -g -Wno-write-strings
INC_DIR = -I../include -I./host -I./sigar -I./scalar -I../utils -I../proto -I../../3rd/protobuf/include -I../../3rd/sigar/include
###########################################################
CC = gcc
XX = g++ 
###########################################################
C_SRC = $(wildcard *.c)
CXX_SRC = $(wildcard *.cpp)
C_OBJS = $(subst .c,.o,$(C_SRC))
CXX_OBJS = $(subst .cpp,.o,$(CXX_SRC))
ALL_OBJ = $(C_OBJS) $(CXX_OBJS)
###########################################################
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_DIR) -std=c99
%.o:%.cpp
	$(XX) $(CFLAGS) -c $< -o $@ $(INC_DIR)
###########################################################

all: $(ALL_OBJ)
	$(MAKE) -C host
	$(MAKE) -C sigar
	$(MAKE) -C scalar

clean:
	$(MAKE) clean -C host
	$(MAKE) clean -C sigar
	$(MAKE) clean -C scalar
	rm -rf *.o

.PHONY: all clean


