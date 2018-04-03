#!/bin/sh

killprog()
{
        pids=$(ps aux | grep $1$ | awk '{print $2}')
        for pid in $pids; do
                kill -9 $pid
        done
}


killprog agentd


