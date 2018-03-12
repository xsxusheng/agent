##c/c++代码编译Makefile
###########################################################

TARGET = agentd
INSTALL_DIR = ../bin
#INC_DIR = -I../rabbitmq/include -I../../log4cplus/include -I./msg -I./utils 
LIB_DIR = -L../3rd/rabbitmq/lib -L../3rd/log4cplus/lib -L../3rd/protobuf/lib
LIB_SF = softlink
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
	$(MAKE) $(LIB_SF)
	$(MAKE) $(TARGET)

$(TARGET): $(ALL_OBJ) 
	$(XX) $^ -o $(TARGET) $(CFLAGS) $(INC_DIR) $(LIB_DEPENDS) $(LIB_DIR)  
	\mv $(TARGET) $(INSTALL_DIR)

$(LIB_SF):
	@cd ../3rd/log4cplus/lib && \
	ln -sf liblog4cplus-1.2.so.5.1.6 liblog4cplus.so && \
	ln -sf liblog4cplus-1.2.so.5.1.6 liblog4cplus-1.2.so.5	
	@cd ../3rd/rabbitmq/lib && \
	ln -sf librabbitmq.so.4.2.1 librabbitmq.so.4 && \
	ln -sf librabbitmq.so.4 librabbitmq.so
	@cd ../3rd/protobuf/lib && \
	ln -sf libprotobuf-lite.so.14.0.0 libprotobuf-lite.so.14 && \
	ln -sf libprotobuf-lite.so.14.0.0 libprotobuf-lite.so && \
	ln -sf libprotobuf.so.14.0.0 libprotobuf.so.14 && \
	ln -sf libprotobuf.so.14.0.0 libprotobuf.so
	
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


