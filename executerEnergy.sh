#!/bin/bash

if [[ $# -lt 1 ]]
then
    echo "usage: ./scriptName en fileToChange"
    exit 1
fi

en=$1
file=$2

inF="in$1MeV.txt"



if [[ ! -f $inF ]]
then
    echo "Input File $inF Does not exist! Please recheck"
    exit 1
fi


if [[ ! -f $file ]]
then
    echo "Macro File $file Does not exist! Please recheck"
    exit 1
fi


source $inF


sed -i "s/.*\/gps\/pos\/centre.*/\/gps\/pos\/centre ${srx} ${sry} 0. mm/g" $file

sed -i "s/.*\/gps\/direction.*/\/gps\/direction ${cosx} ${siny} 0./g" $file

