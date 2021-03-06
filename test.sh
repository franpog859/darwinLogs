#!/usr/bin/env bash

echo "Preparing shell..."
set -o errexit ; set -o nounset
CURRENT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd ${CURRENT_DIR}

echo "Running cmake . ..."
cmake .

if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Export environment variable for MACOS..."
    export CPLUS_INCLUDE_PATH=/usr/local/Cellar/boost/1.69.0_2/include/ #Be sure that it's correct version.
fi

echo "Running make..."
make

echo "Running example usage..." #TODO: Check if it actually works on MACOS
echo "To check memory leaks run: cat valgrind-out.txt"
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./darwinLogs -e=12 -ie=data/env.json -ip=data/pop.json -op=data/output/

echo "Checking memory leaks..."
cat valgrind-out.txt | grep ==