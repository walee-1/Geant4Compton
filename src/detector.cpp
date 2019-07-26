#include "G4VUserDetectorConstruction.hh"
#include "detector.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"

#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"

#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "TrackerSD.hh"
#include "G4PhysicalVolumeStore.hh"

#include "G4UserLimits.hh"

DetectorGeom::DetectorGeom():G4VUserDetectorConstruction(){} //constructor

DetectorGeom::~DetectorGeom(){} //virtual destructor

G4VPhysicalVolume* DetectorGeom::Construct() //virtual function to ensure polymorphism
{
		//setting step limits
		G4UserLimits* myLimits= new G4UserLimits();
		myLimits->SetMaxAllowedStep(0.1*um);

		G4NistManager* nist = G4NistManager::Instance();
		
		//materials for world and target and whatever else, galactic is vacuum
		G4Material* Si=nist->FindOrBuildMaterial("G4_Si");
		G4Material* Al=nist->FindOrBuildMaterial("G4_Al");

		// G4Material* vac=nist->FindOrBuildMaterial("G4_Galactic"); //space to be exact


		//new vacuum definition
		// G4Material* air=G4Material::GetMaterial("G4_AIR");
		// G4double density=10.e-15*g/cm3;
		// G4double pressure=10.e-15*bar;
		// G4double temperature=295.*kelvin;
		// G4int ncomponents=1.;
		// G4double fractionmass=1.;

		G4double density=10.e-15*g/cm3;
		G4double pressure=10.e-12*bar;
		G4double temperature=295.*kelvin;
		G4Element* N=new G4Element("Nitrogen","N",  7.,  14.00674*g/mole);
		G4Element* O=new G4Element("Oxygen",  "O",  8.,  15.9994*g/mole);

		G4Material* vac = new G4Material("Vacuum", density, 2,kStateGas, temperature,pressure);
    	vac-> AddElement(N, .7);
   		vac-> AddElement(O, .3);

		
		//define the world solize, 5x5x5m^3 in my case
		G4double world_sizeX=5./2.*m;
		G4double world_sizeY=5./2.*m;
		G4double world_sizeZ=5./2.*m;
		G4cout<<world_sizeX;
		//creates the shape of the world, which in this case is a square box of 1x1x1
		G4Box* solidWorld=new G4Box("WorldBox", //name of the shape of the world
									world_sizeX,world_sizeY,world_sizeZ); //size of the world (size is halfed because this is in one axis, 
																			//the center expands on both axis)
		
		//creates the world's physical volume by attaching a material to it etc.
		G4LogicalVolume* logicWorld=new G4LogicalVolume(solidWorld, //its shape
										vac, //its material
										"myWorld"); //name of the world
		logicWorld->SetVisAttributes(G4VisAttributes::Invisible); //sets the world invisible
		
		G4VPhysicalVolume* physWorld=new G4PVPlacement(0, //rotation
											G4ThreeVector(), //initial placement of the center
											logicWorld, //logical volume
											"World", //name 
											0, //mother volume
											false, //boolean operations
											0, //copy numner
											true); //check overlap
		
		//shape of the target to fire particles at, creates from center in both axis, so divide the wanted length by 2
		G4double target_sizeX=10./2.*cm;
		G4double target_sizeY=10./2.*cm;
		G4double target_sizeZ=300./2.*um;
		G4Box* solidTarget=new G4Box("TargetSi",target_sizeX,target_sizeY,target_sizeZ);
		
		//create the target logical volume by assigning a material to it
		G4LogicalVolume* logicTargetSi=new G4LogicalVolume(solidTarget,Si,"LogicalVolumeSi");

		//give a name to the region of the Silicon detector for setting production cuts, you call whatever string you pass in G4Region.
		G4Region* detectorSi=new G4Region("detectorSi");
		detectorSi->AddRootLogicalVolume(logicTargetSi);//attach a logical volume to the region.
		detectorSi->SetUserLimits(myLimits);

		G4VisAttributes* siAtt=new G4VisAttributes(G4Colour(0.,0.,1.));//just for visualization purposes, rgb code
		logicTargetSi->SetVisAttributes(siAtt); //set the color to some logical volume

		logicTargetSi->SetUserLimits(myLimits);

		//still under investigation and coding routine, not final AT ALL! 
		// G4String trackerChamberSDname="/Si";
		// TrackerSD* sensitive=new TrackerSD(trackerChamberSDname,"TrackerHitsCollection");

		//TrackerSD* sensitive=new TrackerSD(trackerChamberSDname);
		G4String SDname;
		TrackerSD* sensitive=new TrackerSD(SDname="/active");
		G4SDManager* sdman = G4SDManager::GetSDMpointer();
		sdman->AddNewDetector(sensitive);
		logicTargetSi->SetSensitiveDetector(sensitive);
		//SetSensitiveDetector("LogicalVolumeSi",sensitive,true);

		
		//Al
		G4double target_sizeXAl=target_sizeX;
		G4double target_sizeYAl=target_sizeY;
		G4double target_sizeZAl=10./2.*nm;
		G4Box* solidTargetAl=new G4Box("TargetAl",target_sizeXAl,target_sizeYAl,target_sizeZAl);
		G4LogicalVolume* logicTargetAl=new G4LogicalVolume(solidTargetAl,Al,"LogicalVolumeAl");

		//this makes the detector pretty.
		G4VisAttributes* alAtt=new G4VisAttributes(G4Colour(0.75,0.75,0.75));
		logicTargetAl->SetVisAttributes(alAtt);
		logicTargetAl->SetUserLimits(myLimits);

		//give a name to the region of the aluminum detector for setting production cuts
		G4Region* detectorAl=new G4Region("detectorAl");
		detectorAl->AddRootLogicalVolume(logicTargetAl);



		//Place the detector (target logical volume) inside the world
		new G4PVPlacement(0,
						G4ThreeVector(),
						logicTargetSi,
						"Silicon",
						logicWorld,
						false,
						0,
						true);
		new G4PVPlacement(0,
						G4ThreeVector(0,0,-150.005*um), //since the al is 100nm, and things are placed in the center, 300/2+10/2
						logicTargetAl,
						"Aluminium",
						logicWorld,
						false,
						0,
						true);

	
		return physWorld;
		
}

//...o0o0o0o0o0o0.....00o0o0o0o0o00o0o............o0o0o0o0o0o0o0o0o0.....o0o0o0o0oo0


//This is just for checking purposes, can ignore for now.
void DetectorGeom::CheckOverLaps()
{
	G4PhysicalVolumeStore* thePVStore = G4PhysicalVolumeStore::GetInstance();
	G4cout<<thePVStore->size()<<" physical volumes are defined"<<G4endl;
	G4bool overlapFlag=false;
	G4int res=1000;
	G4double tol=0.;
	for (size_t i=0;i<thePVStore->size();i++){
		overlapFlag=(*thePVStore)[i]->CheckOverlaps(res,tol,true)|overlapFlag;
		}
	if(overlapFlag)
	G4cout<<"Check: there are overlapping volumes"<<G4endl;
}


//...o0o0o0o0o0o0.....00o0o0o0o0o00o0o............o0o0o0o0o0o0o0o0o0.....o0o0o0o0oo0
