#!/usr/bin/env bash

echo "Preparing shell..."
set -o errexit ; set -o nounset
CURRENT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd ${CURRENT_DIR}

echo "Run cmake . ..."
cmake .

if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Export environment variable for MACOS..."
    export CPLUS_INCLUDE_PATH=/usr/local/Cellar/boost/1.69.0_2/include/ #Be sure that it's correct version.
fi

echo "Run make..."
make

echo "Run example usage..."
./darwinLogs -e=12 -ie=data/env.json -ip=data/pop.json -op=data/output/