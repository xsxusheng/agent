##c/c++代码编译Makefile
###########################################################

TARGET = appmsg
CFLAGS = -Wall -O -g -Wno-write-strings
INC_DIR = -I../../3rd/log4cplus/include -I../../../3rd/protobuf/include -I../../../3rd/rabbitmq/include \
	-I../include
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
	$(XX) $(CFLAGS) -c $< -o $@ $(INC_DIR) -std=c++11
###########################################################
all: $(TARGET)
$(TARGET): $(ALL_OBJ)
	@echo $(TARGET)

clean:
	rm -rf *.o $(TARGET)

.PHONY: all clean distclean 


