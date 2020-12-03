#!/bin/bash

SCRIPT_DIR=$(dirname "$(readlink -f -- ${BASH_SOURCE[0]})")


echo "$SCRIPT_DIR"
set -o errexit

fileServer="https://sbforge.org/downloads/scape/scape_xcorrsound_jenkins_files"

echo "Downloading test data"
mkdir -p "$SCRIPT_DIR/data"
cd "$SCRIPT_DIR/data"
wget -r -np -nd -N "$fileServer/" 2> wget.log
cd ..
echo "Test data downloaded"

datadir="$SCRIPT_DIR/data"

for file in $SCRIPT_DIR/*Test.sh; do 
   echo 
   $file "$datadir"
done;
      
        
