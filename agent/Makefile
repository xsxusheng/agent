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
	@[[ ! -d $(TARGET_DIR) ]] || rm -rf $(TARGET_DIR)/*
	@[[ -d $(TARGET_DIR) ]] || mkdir $(TARGET_DIR)
	@find etc/. -name  "[A-Za-z]*" | xargs sed -i 's/\r$///g'
	@find bin/ -name  "*.sh" | xargs sed -i 's/\r$///g'
	@chmod +x install.sh bin/*

	mkdir -p $(AGENT_DIR)/etc $(AGENT_DIR)/bin $(AGENT_DIR)/script
	@\cp -rf etc $(AGENT_DIR)
	@\cp -rf bin $(AGENT_DIR)
	@\cp -rf script $(AGENT_DIR)
	@\cp -f  tool/3rd_img/agent_3rd.tar.gz $(AGENT_DIR)
	@\cp -f install.sh $(TARGET_DIR)

	@tar zcvf $(TARGET_PKG) $(TARGET_DIR)
	@echo "PKG ===> ${TARGET_PKG}"
	@echo ""

clean:
	$(MAKE) clean -C src



