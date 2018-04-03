##c/c++代码编译Makefile
###########################################################
TARGET_DIR = AGENT_R3.0.0.0_3001_CentOS_Linux_release_7.1.1503_Core.x86_64
TARGET_PKG = $(TARGET_DIR).tar.gz
AGENT_DIR = $(TARGET_DIR)/agent


all: agent

agent: 
	$(MAKE) -C src
	@echo "============make end==========================="
pkg:agent
	[[ ! -d $(TARGET_DIR) ]] || rm -rf $(TARGET_DIR)/*
	[[ -d $(TARGET_DIR) ]] || mkdir $(TARGET_DIR)
	mkdir -p $(AGENT_DIR)/lib
	chmod +x install.sh bin/*
	
	\cp -rf bin $(AGENT_DIR)
	\cp -rf etc $(AGENT_DIR)
	\cp -rf script $(AGENT_DIR)
	\cp -f 3rd/log4cplus/lib/* $(AGENT_DIR)/lib/
	\cp -f 3rd/protobuf/lib/libprotobuf*.so* $(AGENT_DIR)/lib
	\cp -f 3rd/rabbitmq/lib/* $(AGENT_DIR)/lib
	\cp 3rd/sigar/lib/* $(AGENT_DIR)/lib
	
	\cp -f install.sh $(TARGET_DIR)

	tar zcvf $(TARGET_PKG) $(TARGET_DIR)
	@echo "to pkg"

clean:
	$(MAKE) clean -C src



