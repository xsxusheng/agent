##c/c++代码编译Makefile
###########################################################

TARGET = agentd
INSTALL_DIR = ../bin
INC_DIR = -I../../rabbitmq/include  -I./msg -I./utils 
LIB_DIR = -L../../rabbitmq/lib 
LIB_DEPENDS = -llog4cplus  -lrabbitmq  -lpthread
CFLAGS = -Wall -O -g -Wno-write-strings

ALL_OBJ = main/*.o utils/*.o msg/*.o  
###########################################################
CC = gcc
XX = g++ 
###########################################################

all:
	$(MAKE) -C utils
	$(MAKE) -C proto
	$(MAKE) -C msg
	$(MAKE) -C main
	$(MAKE) $(TARGET)

$(TARGET):$(ALL_OBJ)
	$(XX) $^ -o $(TARGET) $(CFLAGS) $(INC_DIR) $(LIB_DEPENDS) $(LIB_DIR)  
	\cp $(TARGET) $(INSTALL_DIR)

clean:
	$(MAKE) clean -C proto
	$(MAKE) clean -C msg
	$(MAKE) clean -C utils
	$(MAKE) clean -C main
	rm -rf *.o $(TARGET)
.PHONY: all clean distclean 


