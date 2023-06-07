#ifndef detector_h
#define detector_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4FieldManager.hh"
#include <vector>
#include "MagneticField.hh"
#include "G4UniformMagField.hh"
class G4VPhysicalVolume;
class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class detectorMessenger;


class DetectorGeom : public G4VUserDetectorConstruction{
public:

	DetectorGeom();
	virtual ~DetectorGeom();
	
	virtual G4VPhysicalVolume* Construct();
	virtual void ConstructSDandField();

	void CheckOverLaps();

	void DensitySet(G4double);
	void PressureSet(G4double);
	void TemperatureSet(G4double);
	void gasPropSet(G4double,G4double,G4double);
	virtual void PrintGasParameters();
	void ConstructVacuum(G4double,G4double,G4double);
	void ConstructMuMetalTubes();
	void WidthSet(G4double);

	void setYOffset(G4double);

	void ConstructMaterials();
	void PlaceTubes();
	virtual void UpdateGeometry();
	G4VPhysicalVolume* ConstructWorld();


private:
	detectorMessenger* fDetectorMessenger;
	G4double widthMu3;
	G4Material* vac;
	
	G4VPhysicalVolume* physWorld;
	G4VPhysicalVolume* physTube;
	G4VPhysicalVolume* physTube2;
	G4VPhysicalVolume* physTube3;
	G4VPhysicalVolume* physTube4;
	G4VPhysicalVolume* physPmma;
	G4VPhysicalVolume* physAl;
	void ComputeParameters();
	G4double worldZ;

	G4ThreeVector* rotPos;

    G4GenericMessenger* fMessenger;
    
    MagneticField* fMagneticField;
    G4FieldManager* fFieldMgr;	
	// G4FieldManager* fFieldMgrTube;
	// G4MagneticField* fMagneticFieldTube;
	// fDetectorMessenger(nullptr),vac(nullptr), logicWorld(nullptr), emptyTube3(nullptr),
	// logicMagTube(nullptr), logicTube3(nullptr), logicTube(nullptr), logicTube4(nullptr)

	G4LogicalVolume* logicWorld;

	G4Material* muMetal;
	G4Material* MagMat;
	G4Material* Pmma;
	G4Material* Alu;
	G4Box* solidTube;
	G4Box* solidTube2;
	G4Box* solidTube3;
	G4Box* solidTube4;
	
	G4Box* solidTubeInside3;
	G4Box* solidMag;
	G4Box* solidPmma;
	G4Box* solidAlu;
	G4Box* solidAluInside;
	G4Box* collSrc;
	G4Box* collSrcInside;
	G4Tubs* collTub;
	G4SubtractionSolid* emptyTube;
	G4SubtractionSolid* emptyTube2;
	G4SubtractionSolid* emptyTube3;
	G4SubtractionSolid* emptyTube4;
	G4SubtractionSolid* emptyAlu;
	G4SubtractionSolid* emptySrc;

	G4LogicalVolume* logicMagTube;
	G4LogicalVolume* logicTube3;
	G4LogicalVolume* logicTube;
	G4LogicalVolume* logicAlu;

	G4LogicalVolume* logicTube4;
	G4LogicalVolume* logicPmma;

	G4LogicalVolume* logicSrcColl;


	G4double density,pressure,temperature;
	G4double yOffset;


	G4double tubx;
	G4double tuby;
	G4double tubz;
	G4double boxThickness;
	G4double tubzIn;
	G4double tubyIn;
	G4double tubxIn;

	G4double magx;
	G4double magy;
	G4double magz;

	G4double tub2x;
	G4double tub2y;
	G4double tub2z;

	G4double boxThickness2;
	G4double tub2zIn;
	G4double tub2yIn;
	G4double tub2xIn;

	G4double tub3x;
	G4double tub3y;
	G4double tub3z;
	G4double boxThickness3;
	G4double tub3zIn;
	G4double tub3yIn;
	G4double tub3xIn;

	G4double tub4x;
	G4double tub4y;
	G4double tub4z;
	G4double boxThickness4;
	G4double tub4zIn;
	G4double tub4yIn;
	G4double tub4xIn;

	G4double pmmax;
	G4double pmmay;
	G4double pmmaz;

	G4double alux;
	G4double aluy;
	G4double aluz;
	G4double aluyin;
	G4double aluzin;
	G4double aluxin;

	G4double srclenx;
	G4double srcleny;
	G4double srclenZ;
	G4double srclenxIn;
	G4double srclenyIn;
	G4double srclenZIn;
	G4double srcThickness;

};
inline void DetectorGeom::ComputeParameters()
{
	
	tubzIn=(tubz-boxThickness);
	tubyIn=(tuby-boxThickness);
	tubxIn=(tubx+1);

	tub2zIn=(tub2z-boxThickness2);
	tub2yIn=(tub2y-boxThickness2);
	tub2xIn=tub2x+1;
	tub3zIn=(tub3z-boxThickness3);
	tub3yIn=(tub3y-boxThickness3);
	tub3xIn=tub3x+5;

	tub4zIn=(tub4z-boxThickness4);
	tub4yIn=(tub4y-boxThickness4);
	tub4xIn=tub4x+5;

	srclenxIn=srclenx+1;
	srclenyIn=srcleny-srcThickness;
	srclenZIn=srclenZ-srcThickness;

	alux=tub3x;
	aluy=tub2y;
	aluyin=tub3y;
	aluzin=tub3z;
	aluxin=alux+5;



}
#endif



