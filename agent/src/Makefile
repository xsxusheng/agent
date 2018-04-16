##c/c++代码编译Makefile
###########################################################

TARGET = agentd
INSTALL_DIR = ../bin
INC_DIR = -I./include 
LIB_DIR = -L../3rd/rabbitmq/lib -L../3rd/log4cplus/lib -L../3rd/protobuf/lib -L../3rd/sigar/lib
LIB_SF = softlink
LIB_DEPENDS = -llog4cplus  -lrabbitmq  -lpthread -lprotobuf -lsigar -lxml2
CFLAGS = -Wall -O -g -Wno-write-strings
ALL_OBJ = main/*.o utils/*.o msg/*.o proto/*.o perf/*.o conf/*.o app/*.o 
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
	$(MAKE) -C perf
	$(MAKE) -C main
	$(MAKE) $(LIB_SF)
	$(MAKE) $(TARGET)

$(TARGET): $(ALL_OBJ) 
	@$(XX) $^ -o $(TARGET) $(CFLAGS) $(INC_DIR) $(LIB_DEPENDS) $(LIB_DIR)  
	@\mv $(TARGET) $(INSTALL_DIR)

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
	@cd ../3rd/sigar/lib && \
	ln -sf libsigar.so.0.0.0 libsigar.so && \
	ln -sf libsigar.so.0.0.0 libsigar.so.0
	
clean:
	$(MAKE) clean -C proto
	$(MAKE) clean -C msg
	$(MAKE) clean -C utils
	$(MAKE) clean -C alarm
	$(MAKE) clean -C app
	$(MAKE) clean -C conf
	$(MAKE) clean -C host
	$(MAKE) clean -C perf
	$(MAKE) clean -C main
	rm -rf *.o $(TARGET)
	@cd ../3rd/log4cplus/lib && \
	rm -f liblog4cplus.so && \
	rm -f liblog4cplus-1.2.so.5 
	@cd ../3rd/rabbitmq/lib && \
	rm -f librabbitmq.so && \
	rm -f librabbitmq.so.4 
	@cd ../3rd/protobuf/lib \
	rm -f libprotobuf-lite.so && \
	rm -f libprotobuf-lite.so.14 && \
	rm -f libprotobuf.so && \
	rm -f libprotobuf.so.14 
	@cd ../3rd/sigar/lib && \
	rm -f libsigar.so && \
	rm -f libsigar.so.0

.PHONY: all clean distclean 


