#!/bin/sh
  server_status_code=`ps -aux | grep  'agentd' |grep -v grep| wc -l`
  if [ $server_status_code -lt 1  ]; then
        echo "stoped"
        exit 0
  else
       echo "started"
       exit 0
  fi
