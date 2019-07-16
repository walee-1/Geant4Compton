#ifndef detector_h
#define detector_h 1

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;


class DetectorGeom : public G4VUserDetectorConstruction{
public:

	DetectorGeom();
	virtual ~DetectorGeom();
	
	virtual G4VPhysicalVolume* Construct();

	void CheckOverLaps();
	
};
#endif



