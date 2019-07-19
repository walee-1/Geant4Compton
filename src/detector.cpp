#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "detector.hh"
#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4RotationMatrix.hh"

#include "G4PhysicalVolumeStore.hh"

DetectorGeom::DetectorGeom():G4VUserDetectorConstruction(){} //constructor

DetectorGeom::~DetectorGeom(){} //virtual destructor

G4VPhysicalVolume* DetectorGeom::Construct() //virtual function to ensure polymorphism
{
		G4NistManager* nist = G4NistManager::Instance();
		
		//materials for world and target and whatever else, galactic is vacuum
		G4Material* Si=nist->FindOrBuildMaterial("G4_Si");
		G4Material* vac=nist->FindOrBuildMaterial("G4_Galactic"); //space to be exact
		G4Material* Al=nist->FindOrBuildMaterial("G4_Al");

		//new vacuum definition
		// G4Material* air=G4Material::GetMaterial("G4_AIR");
		G4double density=10.e-15*g/cm3;
		G4double pressure=10.e-12*bar;
		G4double temperature=295*kelvin;
		G4int ncomponents;
		G4double fractionmass;

		// G4Material* vacuum10=new G4Material("Vacuum10",density,ncomponents=1,kStateGas,temperature,pressure);
		// vacuum10->AddMaterial(air,fractionmass=1.);

		G4double z,a;

		a = 14.01*g/mole;
		G4Element* elN = new G4Element("Nitrogen","N" , z= 7., a);
		
		a = 16.00*g/mole;
		G4Element* elO = new G4Element("Oxygen","O" , z= 8., a);
		
		G4Material* vacuum = new G4Material("Vacuum",density,ncomponents=2,kStateGas,temperature,pressure);
		vacuum->AddElement(elN, fractionmass=70*perCent);
		vacuum->AddElement(elO, fractionmass=30*perCent);

		
		//define the world solize, 1x1x1 in my case
		G4double world_sizeX=5./2.*m;
		G4double world_sizeY=5./2.*m;
		G4double world_sizeZ=5./2.*m;
		G4cout<<world_sizeX;
		//creates the shape of the world, which in this case is a square box of 1x1x1
		G4Box* solidWorld=new G4Box("World", //name of the shape of the world
									world_sizeX,world_sizeY,world_sizeZ); //size of the world (size is halfed because this is in one axis, 
																			//the center expands on both axis)
		
		//creates the world's physical volume by attaching a material to it etc.
		G4LogicalVolume* logicWorld=new G4LogicalVolume(solidWorld, //its shape
										vacuum, //its material
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
		//G4VPhysicalVolume* physWorld=newG4PVPlacement(no rotation, at origin, logical volume it is in, name, mother volume, no boolean operation, copy number, overlaps checking);
		
		//shape of the target to fire particles at
		G4double target_sizeX=10./2.*cm;
		G4double target_sizeY=10. /2.*cm;
		G4double target_sizeZ=300./2.*um;
		G4Box* solidTarget=new G4Box("Target",target_sizeX,target_sizeY,target_sizeZ);
		
		//create the target logical volume by assigning a material to it
		G4LogicalVolume* logicTargetSi=new G4LogicalVolume(solidTarget,Si,"detectorSi");

		G4VisAttributes* siAtt=new G4VisAttributes(G4Colour(1.,0.,0.));
		logicTargetSi->SetVisAttributes(siAtt);

		
		//Al
		G4double target_sizeXAl=target_sizeX;
		G4double target_sizeYAl=target_sizeY;
		G4double target_sizeZAl=100./2.*nm;
		G4Box* solidTargetAl=new G4Box("Target2",target_sizeXAl,target_sizeYAl,target_sizeZAl);
		G4LogicalVolume* logicTargetAl=new G4LogicalVolume(solidTargetAl,Al,"detectorAl");

		G4VisAttributes* alAtt=new G4VisAttributes(G4Colour(0.,0.,1.));
		logicTargetAl->SetVisAttributes(alAtt);
		
		G4Tubs* Tube=new G4Tubs("Test Tube",7.*cm,10.*cm,10.*cm,0.*deg,360.*deg);
		G4LogicalVolume* logTube=new G4LogicalVolume(Tube,Al,"AlTube");
		G4VisAttributes* tubeatt=new G4VisAttributes(G4Colour(0.,1.,0.));
		logTube->SetVisAttributes(tubeatt);

		//G4VSensitiveDetector* sensitiveBox=new MySensitiveDetector("/MyDetector");

		// G4SDManager* pSDManager=G4SDManager::GetSDMpointer();
		// pSDManager->AddNewDetector(sensitiveBox);
		// logicTargetSi->SetSensitiveDetector(sensitiveBox);



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
							G4ThreeVector(0,0,-150.075*um),
							logicTargetAl,
							"Aluminium",
							logicWorld,
							false,
							0,
							true);

		G4RotationMatrix* Rot=new G4RotationMatrix;
		Rot->rotateY(M_PI/2.*rad);
		Rot->rotateX(90.*deg);

		new G4PVPlacement(Rot,G4ThreeVector(0,0,50.*cm),logTube,"AlTube",logicWorld,false,0,true);

		return physWorld;
		
}


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



