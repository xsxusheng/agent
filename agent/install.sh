#!/bin/sh

agent_dir=/opt/fonsview/NE/agent
lib_dir=/opt/fonsview/NE/agent/lib

#force install
force=$1
if [ "x${force}" = "x-f" ];then
	\rm -rf ${agent_dir}
	mkdir -p ${agent_dir}
	mkdir -p ${agent_dir}/log
	\cp -rf ./agent/etc ${agent_dir}
else
	mkdir -p ${agent_dir}
	mkdir -p ${agent_dir}/log
fi

\cp -rf ./agent/bin ${agent_dir}
\cp -rf ./agent/script ${agent_dir}
\rm -rf ${lib_dir}
tar zxf ./agent/agent_3rd.tar.gz -C ${agent_dir}

count=`cat /etc/ld.so.conf | grep "${lib_dir}" | wc -l`
if [ $count -lt 1 ];then
	echo ${lib_dir} >> /etc/ld.so.conf
fi
ldconfig 2>&1 1>/dev/null

echo "install successfully"
