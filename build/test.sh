#!/bin/bash
source /usr/local/bin/geant4.sh
#
#rm fulltrack.txt
#
./test_example << EOF
/control/verbose 2
/control/saveHistory
/run/verbose 2
/run/initialize
/vis/open HepRepFile
/vis/drawVolume
/vis/viewer/flush
/vis/scene/add/trajectories smooth
/vis/scene/endOfEventAction accumulate
/run/beamOn 36
exit
EOF