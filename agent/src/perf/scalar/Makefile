##c/c++代码编译Makefile
###########################################################

TARGET = perf
CFLAGS = -Wall -O -g -Wno-write-strings
INC_DIR = -I../../include -I../sigar -I../host -I../../utils -I../../proto -I../../../3rd/protobuf/include -I../../../3rd/sigar/include
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
all: $(TARGET)
$(TARGET): $(ALL_OBJ)
	@cp $(ALL_OBJ) ../

clean:
	rm -rf *.o

.PHONY: all clean


