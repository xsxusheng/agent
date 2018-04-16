#!/bin/sh 
curdir="$(cd "$(dirname "$0")" && pwd)"
make pkg -C $curdir
