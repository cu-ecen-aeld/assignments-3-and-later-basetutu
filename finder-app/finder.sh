#!/bin/bash

# number of files and folders in a directory:
# ls | wc -l

# Find Number of Files in a Directory recursively:
# find ~/repo/repo_study/delete/ -type f -print | wc -l

# number of none hidden directory:
# ls -l | grep ^d | wc -l
# ls -lR ~/repo/repo_study/delete | grep ^d | wc -l

filesdir=${1%/}  # will take the script's first parameter and remove a trailing slash if there is one.
searchstr=$2

if [[ $filesdir == "" ]]
then
    echo "Error: No input arguments were given."
    exit 1
elif [[ $searchstr == "" ]]
then
    echo "Error: The search string argument was not given."
    exit 1
fi

# Check the path for being a directory:
if [ ! -d "$filesdir" ]
then
    echo "Directory '$filesdir' is not a directory or does not exists."
    exit 1
fi

echo "Searching recursively in all files:"
echo "-----------------------------------"
echo "Directory:   '$filesdir'"
echo "Search for:  '$searchstr'"

# We silence non-error output by redirecting stdout (1) to /dev/null:
nbrOfSubDir=$(ls -lR $filesdir | grep ^d | wc -l)
echo "nbr of sub-directories to search in: $nbrOfSubDir"

nbrOfFiles=$(find $filesdir -type f -print | wc -l)
nbrOfMatchingLines=$(grep -r $searchstr $filesdir | wc -l)
echo "The number of files are $nbrOfFiles and the number of matching lines are $nbrOfMatchingLines"
