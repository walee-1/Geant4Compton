#!/bin/bash

#source env.sh

physicsList=(empenelope emlivermore emstandard_opt4)

##checking the arguments
if [[($# -eq 0)]]; then
    echo "Usage: $0 Energy_range_start Energy_Range_end step_size particle_type end_of_range_histo"
    echo "By default, Energy_range_end = 0 and step_size = 0, particle type and end of range remains untouched"
    exit 1
fi

if [[($# -lt 2)]]; then
    energyend=$1;
    energystep=1;
    energystart=$1;
    particle=0;
    end_range=0;
fi

if [[($# -lt 4 && $# -gt 2)]]; then
    energyend=$2;
    energystep=$3;
    energystart=$1;
    particle=0;
    end_range=0;
fi

if [[($# -eq 4)]]; then
    energyend=$2;
    energystep=$3;
    energystart=$1;
    particle=$4;
    end_range=0;
fi

if [[($# -eq 5)]]; then
    energyend=$2;
    energystep=$3;
    energystart=$1;
    particle=$4;
    end_range=$5;
fi

config_file=init_vis.mac
record_dir=root_data
`mkdir -p $record_dir`

running_thingy(){
    ./test_example ${config_file} &
    pid=$!
    sleep 1;
    wait $pid
}

if [[ ${particle} != 0 ]]; then
            sed -i -re "s+/gps/particle [0-9,a-z,\-]*+/gps/particle ${particle}+g" ${config_file};
fi

for i in "${physicsList[@]}"
do 
    sed -i -e "s+/testem/phys/addPhysics [0-9,a-z,A-Z,\_]*+/testem/phys/addPhysics $i+g" ${config_file};
    for en in `seq ${energystart} ${energystep} ${energyend}`;
    do
        en2=${en//,/.}
        en_for_histo=$(expr $en2*1000 | bc)
        if [[ ${end_range} != 0 ]]; then
           sed -i -re "s+/analysis/h1/set 2 3000 -150.5 [0-9,\.,\-]*+/analysis/h1/set 2 3000 -150.5 ${end_range}+g" ${config_file};
           sed -i -re "s+/analysis/h1/set 4 3000 -150.5 [0-9,\.,\-]*+/analysis/h1/set 4 3000 -150.5 ${end_range}+g" ${config_file};
           sed -i -re "s+/analysis/h1/set 5 3000 -150.5 [0-9,\.,\-]*+/analysis/h1/set 5 3000 -150.5 ${end_range}+g" ${config_file};
        fi
        sed -i -re "s+/analysis/h1/set 1 3000 0 [0-9,\.,\,]*+/analysis/h1/set 1 3000 0 ${en_for_histo}+g" ${config_file};
        sed -i -re "s+/analysis/h1/set 3 3000 0 [0-9,\.,\,]*+/analysis/h1/set 3 3000 0 ${en_for_histo}+g" ${config_file};
        sed -i -re "s+/analysis/h1/set 6 3000 0 [0-9,\.,\,]*+/analysis/h1/set 6 3000 0 ${en_for_histo}+g" ${config_file};
        sed -i -e "s+/gps/ene/mono [0-9,\.,\,]* keV+/gps/ene/mono ${en2} keV+g" ${config_file};
        running_thingy
        sleep 1
        mv -f output.root ${record_dir}/output_${i}_${en2}.root 2>/dev/null &
        pid=$!
        echo -e "moving file"
        wait $pid

    done
done