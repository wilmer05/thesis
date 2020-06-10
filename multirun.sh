#! /bin/bash

for var in "${@:2}"
do
    ./src/run $1 $var 800 > ./experiments/$1_$var.exp &
done
