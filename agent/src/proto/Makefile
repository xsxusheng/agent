##c/c++代码编译Makefile
###########################################################

TARGET = proto
CFLAGS = -Wall -O -g -Wno-write-strings
INC_DIR = -I../../3rd/protobuf/include
###########################################################
CC = gcc
XX = g++
###########################################################
C_SRC = $(wildcard *.c)
CXX_SRC = $(wildcard *.cc)
C_OBJS = $(subst .c,.o,$(C_SRC))
CXX_OBJS = $(subst .cc,.o,$(CXX_SRC))
ALL_OBJ = $(C_OBJS) $(CXX_OBJS)
###########################################################
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_DIR) -std=c99
%.o:%.cc
	$(XX) $(CFLAGS) -c $< -o $@ $(INC_DIR)
###########################################################
all: $(TARGET)
$(TARGET): $(ALL_OBJ)
	@echo $(TARGET)

clean:
	rm -rf *.o $(TARGET)

.PHONY: all clean


