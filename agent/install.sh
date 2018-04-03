#!/bin/sh

#force install
agent_dir=/opt/fonsview/NE/agent
lib_dir=/opt/fonsview/NE/agent/lib

if [ -d ${install_dir} ];then
	rm -rf ${agent_dir}
fi
mkdir -p ${agent_dir}
mkdir -p ${agent_dir}/log

\cp -rf ./agent/* ${agent_dir}

echo ${lib_dir} >> /etc/ld.so.conf
ldconfig 2>&1 1>/dev/null

echo "install successfully"
