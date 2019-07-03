#!/bin/bash

source /usr/local/bin/geant4.sh
./test_example << EOF
/control/verbose 2
/control/saveHistory
/run/verbose 2
/source/type gps
/gps/particle electron
/gps/pos/type Point
/gps/position 0.0 921.622 -1475.0 mm
/gps/direction 3.39533 9526.5 25703.
/gps/ene/mono 751 keV
/run/initialize
analysis/h1/create 0 0 200 100 1000
analysis/h1/setTitle 0 EdgeEffect_Spin=-1_01
/vis/open HepRepFile
/vis/drawVolume
/vis/viewer/flush
/vis/scene/add/trajectories smooth
/run/beamOn 1
exit
EOF
