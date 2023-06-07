#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 filename"
    exit 0
fi

if [ $# -ge 1 ]; then
    fileName=$1
fi

if [ ! -d Results ]; then
    mkdir -p Results
fi
outDir="./Results/$fileName"
mv "InputEn.txt" $outDir"_InputEn.txt"
mv "output_All.txt" $outDir"_outputAll.txt"
mv "output.txt" $outDir"_output.txt"
mv "output.root" $outDir"_output.root"
mv "Secondary_output.txt" $outDir"_secondary.txt"
