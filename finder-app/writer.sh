#!/bin/bash

writefile=$1
writestr=$2

# echo $#
# if [ $# -le 1 ]
# then
#     echo "less than 2 arguments given"
#     exit 1
# fi

if [[ $writefile == "" ]]
then
    echo "Error: No input arguments were given."
    exit 1
elif [[ $writestr == "" ]]
then
    echo "Error: The write string argument was not given."
    exit 1
fi

# Check the path for being a directory:
if [ -d "$writefile" ]
then
    echo "The path given is not a file-path. ($writefile)"
    exit 1
fi

# Write to file:
mkdir -p `dirname $writefile`  # Create directory in case the location/directory path does not exists.
echo $writestr > $writefile
if [ $? -ne 0 ]
then
    echo "Could not write to file."
    exit 1
fi
