#！/bin/sh

bindir="$(cd "$(dirname "$0")" && pwd)"

${bindir}/agentd &

echo "start agentd"