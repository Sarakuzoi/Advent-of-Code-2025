#!/bin/bash
if [ "$#" -ne 1 ]; then
    echo "You must provide the program file as an argument"
    exit 1
fi

file="$1"
file_name=${file%.cpp}

if [ $? -ne 0 ]; then
    echo "File provided is not C++ file"
    exit 1
fi

g++ --std=c++17 -o "output/$file_name" "$1"

if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

echo "Processing \`input.in\`"
./output/"$file_name" < "input.in" > "password.ans"
echo "Result in \`password.ans\`: `cat password.ans`"