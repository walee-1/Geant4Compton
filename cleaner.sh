#!/bin/bash


rm "InputEn.txt" 
rm "output_All.txt" 
rm "output.txt" 
rm "output.root" 
rm "Secondary_output.txt" 

if [ $# -ge 1 ]; then
    rm "InputEn_old.txt" 
    rm "output_All_old.txt" 
    rm "output_old.txt" 
    rm "output_old.root" 
    rm "Secondary_output_old.txt" 
fi