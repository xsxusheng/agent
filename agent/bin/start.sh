#!/bin/sh

bindir="$(cd "$(dirname "$0")" && pwd)"

${bindir}/stop.sh
${bindir}/agentd &

echo "start agentd"
