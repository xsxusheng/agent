##c/c++代码编译Makefile
###########################################################

TARGET = agentd
INSTALL_DIR = ../bin
#INC_DIR = -I../rabbitmq/include -I../../log4cplus/include -I./msg -I./utils 
LIB_DIR = -L../3rd/rabbitmq/lib -L../3rd/log4cplus/lib -L../3rd/protobuf/lib
LIB_DEPENDS = -llog4cplus  -lrabbitmq  -lpthread -lprotobuf
CFLAGS = -Wall -O -g -Wno-write-strings
ALL_OBJ = main/*.o utils/*.o msg/*.o proto/*.o
###########################################################
CC = gcc
XX = g++ 
###########################################################

all:
	$(MAKE) -C utils
	$(MAKE) -C proto
	$(MAKE) -C msg
	$(MAKE) -C alarm
	$(MAKE) -C app
	$(MAKE) -C conf
	$(MAKE) -C host
	$(MAKE) -C main
	$(MAKE) $(TARGET)

$(TARGET):$(ALL_OBJ)
	$(XX) $^ -o $(TARGET) $(CFLAGS) $(INC_DIR) $(LIB_DEPENDS) $(LIB_DIR)  
	\mv $(TARGET) $(INSTALL_DIR)

clean:
	$(MAKE) clean -C proto
	$(MAKE) clean -C msg
	$(MAKE) clean -C utils
	$(MAKE) clean -C alarm
	$(MAKE) clean -C app
	$(MAKE) clean -C conf
	$(MAKE) clean -C host
	$(MAKE) clean -C main
	rm -rf *.o $(TARGET)

.PHONY: all clean distclean 


