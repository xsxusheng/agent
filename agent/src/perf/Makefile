##c/c++代码编译Makefile
###########################################################

###########################################################
CC = gcc
XX = g++ 
###########################################################

all:
	$(MAKE) -C host
	$(MAKE) -C sigar
	$(MAKE) -C scalar

clean:
	$(MAKE) clean -C host
	$(MAKE) clean -C sigar
	$(MAKE) clean -C scalar

.PHONY: all clean


