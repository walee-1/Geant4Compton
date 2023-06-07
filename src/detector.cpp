#include "detector.hh"
#include "detectorMessenger.hh"


#include "G4NistManager.hh"
#include "G4Material.hh"

#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
 #include "TrackerSD.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4Transform3D.hh"
#include "MagneticField.hh"
#include "G4GeometryManager.hh"

#include "G4RegionStore.hh"


//#include "G4UserLimits.hh"




//REASONS for USING DUMMY MATERIALS: it was for debugging purposes as I was getting weird vacuum conditions, later I found out that it was due to the fact
//that I was redifining density somewhere and when the function was recalled it changed the vacuum density as well, leading to errors.
//later I just didn't bother changing it as this was it is less error prone for me.


DetectorGeom::DetectorGeom()
:G4VUserDetectorConstruction(),fDetectorMessenger(nullptr),vac(nullptr), logicWorld(nullptr), emptyTube3(nullptr),
logicMagTube(nullptr), logicTube3(nullptr), logicTube(nullptr), logicTube4(nullptr)
{
	
	fDetectorMessenger = new detectorMessenger(this);

	density=1.12e-6*g/centimeter3;
	pressure=1.e-3*bar;
	temperature=298.15*kelvin;
	widthMu3=5*mm;
	yOffset=20*mm;
	tubx=165*mm;
	tuby=14.*mm;
	tubz=6*mm;
	boxThickness=1.*mm;

	srclenx=5*mm;
	srcleny=5*mm;
	srclenZ=5*mm;
	srcThickness=4.5*mm;

	magx=50*mm;
	magy=100.*mm;
	magz=100.*mm;

	tub2x=72*mm;
	tub2y=84.*mm;
	tub2z=20.*mm;
	boxThickness2=1.*mm;

	tub3x=22*mm;
	tub3y=widthMu3;
	tub3z=32*mm;
	boxThickness3=1.*mm;

	tub4x=10.2*mm;
	tub4y=8.*mm;
	tub4z=20.*mm;
	boxThickness4=1.*mm;

	pmmax=9.8*mm;
	pmmay=35.*mm;
	pmmaz=35.*mm;

	aluz=60*mm;
	ComputeParameters();



	
} //constructor

DetectorGeom::~DetectorGeom(){
	delete fDetectorMessenger;
} //virtual destructor

G4VPhysicalVolume* DetectorGeom::ConstructWorld()
{
	ConstructVacuum(density,pressure,temperature);

	ConstructMaterials();
	ComputeParameters();
	ConstructMuMetalTubes();

	//define the world solize, 5x5x5m^3 in my case
	G4double world_sizeX=50*m;
	G4double world_sizeY=50./2.*m;
	// G4double world_sizeZ=29.2*cm;
	// G4double world_sizeZ=28.71*cm;
	G4double world_sizeZ=31./2.*m;

	//creates the shape of the world, which in this case is a square box of 1x1x1
	G4Box* solidWorld=new G4Box("WorldBox", //name of the shape of the world
								world_sizeX,world_sizeY,world_sizeZ); //size of the world (size is halfed because this is in one axis, 
																		//the center expands on both axis)
	
	//creates the world's physical volume by attaching a material to it etc.
	logicWorld=new G4LogicalVolume(solidWorld, //its shape
									vac, //its material
									"myWorld"); //name of the world
	logicWorld->SetVisAttributes(G4VisAttributes::Invisible); //sets the world invisible

	physWorld=new G4PVPlacement(0, //rotation
										G4ThreeVector(0*mm,0,0), //initial placement of the center
										logicWorld, //logical volume
										"World", //name 
										0, //mother volume
										false, //boolean operations
										0, //copy numner
										true); //check overlap
	

	PlaceTubes();
	PrintGasParameters();
	CheckOverLaps();
	return physWorld;
}
// Main function which initializes everything and calls all the functions.
G4VPhysicalVolume* DetectorGeom::Construct() //virtual function to ensure polymorphism
{

	return ConstructWorld();
		
}




//...o0o0o0o0o0o0.....00o0o0o0o0o00o0o............o0o0o0o0o0o0o0o0o0.....o0o0o0o0oo0



//  this makes the vaumm and assigns Nitrogen and Oxygen to it. Temperature, density and gas are needed for it but they can be changed dynamically
void DetectorGeom::ConstructVacuum(G4double dens, G4double pres, G4double temp)
{

		G4Element* N=new G4Element("Nitrogen","N",  7.,  14.00674*g/mole);
		G4Element* O=new G4Element("Oxygen",  "O",  8.,  15.9994*g/mole);
		G4Material* vacuum = new G4Material("Vacuum", dens, 2,kStateGas, temp,pres);

		vacuum-> AddElement(N, .7);
   		vacuum-> AddElement(O, .3);
		vac=vacuum;
		

}
// ..o0o0o0o0o0o0o0o0o0o0o0o0o0o
//Functions to change Gas properties start here. These can be done on run time by calling the G4RunManager. Pressure set sets pressure
//tempset sets temperature etc. gaspropset can be used to assign all 3 quantities at once. You can write a function to calculate density if you wish


void DetectorGeom::PressureSet(G4double pres)
{
		pressure=pres;


		UpdateGeometry();

}
void DetectorGeom::DensitySet(G4double dens)
{
		density=dens;

		UpdateGeometry();

}
void DetectorGeom::TemperatureSet(G4double temp)
{
		temperature=temp;
		ConstructVacuum(density,pressure,temperature);
		
		UpdateGeometry();

}
void DetectorGeom::gasPropSet(G4double dens,G4double pres, G4double temp)
{
		density=dens;
		pressure=pres;
		temperature=temp;

		UpdateGeometry();

}

void DetectorGeom::PrintGasParameters()
{
  G4cout << "\n-------------------------------------------------------------"
         << "\n ---> The density is " << vac->GetDensity()/(g/cm3) <<"g/cm3"
		 << "\n ---> The pressure is " <<vac->GetPressure()/bar <<"bar"
		 << "\n ---> The temperature is " << vac->GetTemperature() << "kelvin"
		 << "\n ---> The width of MuMetal 3 is " << widthMu3/mm <<"mm";
  G4cout << "\n-------------------------------------------------------------\n"
         << G4endl;
}

//..o0o0o0o0o0o0o0o0o0o0o0o0o0

//Function to change the width of the aperture tube 
void DetectorGeom::WidthSet(G4double width){
	widthMu3=width+1;

	UpdateGeometry();
}

void DetectorGeom::setYOffset(G4double yoff){

		yOffset=yoff;

		UpdateGeometry();
		
}
//Function to place all parts of the experiment in the world volume. For changes in geometry this and constructtubes have to be edited
void DetectorGeom::PlaceTubes()
{
	//make changes here for angles and position for different energies

	G4double phi=21.542*deg;
	G4double posy=10.442*mm;
	G4double posx=-25.35*mm;
	//end of changes here

	logicSrcColl=new G4LogicalVolume(emptySrc,Alu,"SrcColl");

	logicTube=new G4LogicalVolume(emptyTube,muMetal,"Tube");

	
	
		G4double xOff=(posx-solidTube->GetXHalfLength()*std::cos(phi)); 
		G4double yOff=(posy-solidTube->GetXHalfLength()*std::sin(phi));

		G4double xOffSrc=(posx-solidTube->GetXHalfLength()*2*std::cos(phi)-collSrc->GetXHalfLength()*std::cos(phi));
		G4double yOffSrc=(posy-solidTube->GetXHalfLength()*2*std::sin(phi)-collSrc->GetXHalfLength()*std::sin(phi));
		// G4cout<<"xOFF SRC IS "<<G4endl;
		// G4cout<<xOffSrc<<G4endl;
		// G4cout<<yOffSrc;
		// G4cout<<G4endl;
		G4Transform3D transformSrcColl=G4Translate3D(G4ThreeVector(xOffSrc,yOffSrc,0))*G4RotateZ3D(phi);	
		G4Transform3D transformPosTube1=G4Translate3D(G4ThreeVector(xOff,yOff,0))*G4RotateZ3D(phi);



	
		G4cout<<"\n --> offset = "<<yOff<<G4endl;	


		physTube=new G4PVPlacement(					transformPosTube1,
													logicTube,
													"Tubes",
													logicWorld,
													false,
													0,
													true);

		G4VisAttributes* tub1=new G4VisAttributes(G4Colour(0.,1.,0.));//just for visualization purposes, rgb code
		logicTube->SetVisAttributes(tub1); //set the color to some logical volume


		new G4PVPlacement(					transformSrcColl,
													logicSrcColl,
													"SrcColl",
													logicWorld,
													false,
													0,
													true);
		G4VisAttributes* src1=new G4VisAttributes(G4Colour(0.,1.,0.));//just for visualization purposes, rgb code
		logicSrcColl->SetVisAttributes(src1); //set the color to some logical volume

		logicMagTube = new G4LogicalVolume(solidMag,vac,"magnetLogic");

		new G4PVPlacement(0,
													G4ThreeVector(0.,0.,0.),
													logicMagTube,
													"Magnet",
													logicWorld,
													false,
													0,
													true);
		G4VisAttributes* Mag=new G4VisAttributes(G4Colour(1.,0.,1.));//just for visualization purposes, rgb code
		





		logicMagTube->SetVisAttributes(Mag); //set the color to some logical volume
		G4double offset=solidMag->GetXHalfLength()+solidTube2->GetXHalfLength();
		G4LogicalVolume* logicTube2=new G4LogicalVolume(emptyTube2,muMetal,"Tube2");
		physTube2=new G4PVPlacement(0,
													G4ThreeVector(offset,0.,0.),
													logicTube2,
													"Tube2",
													logicWorld,
													false,
													0,
													true);
		G4VisAttributes* tub2=new G4VisAttributes(G4Colour(0.,1.,0.));//just for visualization purposes, rgb code
		logicTube2->SetVisAttributes(tub2); //set the color to some logical volume

		G4double offset3=solidMag->GetXHalfLength()+solidTube2->GetXHalfLength()*2+solidTube3->GetXHalfLength();
		
		logicTube3=new G4LogicalVolume(emptyTube3,muMetal,"Tube3");
		physTube3=new G4PVPlacement(0,
													G4ThreeVector(offset3,yOffset,0.),
													logicTube3,
													"Tube3",
													logicWorld,
													false,
													0,
													true);
		G4VisAttributes* tub3=new G4VisAttributes(G4Colour(0.,0.,1.));//just for visualization purposes, rgb code
		logicTube3->SetVisAttributes(tub3); //set the color to some logical volume




		G4double offset4=solidMag->GetXHalfLength()+solidTube2->GetXHalfLength()*2+solidTube3->GetXHalfLength()*2+solidTube4->GetXHalfLength();


		logicTube4=new G4LogicalVolume(emptyTube4,muMetal,"Tube4");
		physTube4=new G4PVPlacement(0,
													G4ThreeVector(offset4,yOffset,0.),
													logicTube4,
													"Tube4",
													logicWorld,
													false,
													0,
													true);
		G4VisAttributes* tub4=new G4VisAttributes(G4Colour(1.,0.5,0.));//just for visualization purposes, rgb code
		logicTube4->SetVisAttributes(tub4); //set the color to some logical volume
				logicAlu=new G4LogicalVolume(emptyAlu,Alu,"AluminiumBlock");
		physAl=new G4PVPlacement(0,
													G4ThreeVector(offset3,yOffset,0.),
													logicAlu,
													"Aluminium",
													logicWorld,
													false,
													0,
													true);
		logicAlu->SetVisAttributes(G4VisAttributes(G4Color(0.5,0.7,0.7)));
		//logicAlu->SetVisAttributes(G4VisAttributes::Invisible); 
		logicPmma=new G4LogicalVolume(solidPmma,Pmma,"LogicalVolumePmma");
		G4double offsetPmma=solidMag->GetXHalfLength()+solidTube2->GetXHalfLength()*2+solidTube3->GetXHalfLength()*2+solidTube4->GetXHalfLength()*2
							+solidPmma->GetXHalfLength();
		
		physPmma=new G4PVPlacement(0,
													G4ThreeVector(offsetPmma,yOffset,0.),
													logicPmma,
													"Pmma",
													logicWorld,
													false,
													0,
													true);
		
		// logicPmma->SetVisAttributes(G4VisAttributes::Invisible); 

	
}
//Function to assign all the material out of which we will construct our tubes, detection surface etc.
void DetectorGeom::ConstructMaterials()
{
		std::vector<G4String> elements;
		std::vector<G4int> natoms;

		G4NistManager* nist = G4NistManager::Instance();
		G4Element* iron=nist->FindOrBuildElement("Fe");	
		G4Element* nick=nist->FindOrBuildElement("Ni");
		G4Element* moly=nist->FindOrBuildElement("Mo");
		G4Element* si=nist->FindOrBuildElement("Si");
		G4double densMu=8.7*g/cm3;
		G4Material* muMetaldummy=new G4Material("MuMetal",densMu,4,kStateSolid);
		muMetaldummy->AddElement(nick,.8);
		muMetaldummy->AddElement(moly,.045);	
		muMetaldummy->AddElement(si,.005);
		muMetaldummy->AddElement(iron,.15);

		muMetal=muMetaldummy;

		elements.push_back("C");
		elements.push_back("H");
		elements.push_back("O");
		natoms.push_back(5);
		natoms.push_back(8);
		natoms.push_back(2);
		G4double densityPmma=1.190*g/cm3;

		G4Material* Pmmadummy=nist->ConstructNewMaterial("PMMA",elements,natoms,densityPmma);
		Pmma=Pmmadummy;
		elements.clear();
		natoms.clear();

		G4Material* AluDummy=new G4Material("Aluminium",13,26.98154*g/mole,2.7*g/cm3);
		Alu=AluDummy;

}
//This function construcs the actual mu metal tubes by hollowing them out and defining their area etc
void DetectorGeom::ConstructMuMetalTubes()
{
		solidTube=new G4Box("TubeBox",tubx/2.,tuby/2.,tubz/2.);
		G4Box* solidTubeInside=new G4Box("InnerBox",tubxIn/2.,tubyIn/2,tubzIn/2.);
		emptyTube=new G4SubtractionSolid("hollowTube",solidTube,solidTubeInside);


		solidMag=new G4Box("magnet",magx/2.,magy/2.,magz/2.);

		solidTube2=new G4Box("TubeBox2",tub2x/2.,tub2y/2.,tub2z/2.);
		G4Box* solidTubeInside2=new G4Box("InnerBox2",tub2xIn/2.,tub2yIn/2,tub2zIn/2.);
		emptyTube2=new G4SubtractionSolid("hollowTube2",solidTube2,solidTubeInside2);

		solidTube3=new G4Box("TubeBox3",tub3x/2.,tub3y/2.,tub3z/2.);
		solidTubeInside3=new G4Box("InnerBox3",tub3xIn/2.,tub3yIn/2,tub3zIn/2.);
		emptyTube3=new G4SubtractionSolid("hollowTube3",solidTube3,solidTubeInside3);


		solidTube4=new G4Box("TubeBox4",tub4x/2.,tub4y/2.,tub4z/2.);
		G4Box* solidTubeInside4=new G4Box("InnerBox4",tub4xIn/2.,tub4yIn/2,tub4zIn/2.);
		emptyTube4=new G4SubtractionSolid("hollowTube43",solidTube4,solidTubeInside4);


		solidPmma=new G4Box("TargetPmma",pmmax/2,pmmay/2,pmmaz/2);


		solidAlu=new G4Box("AluBox",alux/2,aluy/2,aluz/2);
		solidAluInside=new G4Box("InnerAluBox",aluxin/2,aluyin/2,aluzin/2);
		emptyAlu=new G4SubtractionSolid("hollowAlu",solidAlu,solidAluInside);

		collSrc=new G4Box("SourceCollimator",srclenx/2,srcleny/2,srclenZ/2);
		collSrcInside=new G4Box("InnerSrcBox",srclenxIn/2,srclenyIn/2,srclenZIn/2);
		emptySrc=new G4SubtractionSolid("hollowSrcColl",collSrc,collSrcInside);

}
//Archaic function/still in work. Not sure which direction I will take


//Function which assigns the sensitive detector area and the magnetic field region! This is called automatically by Geant so no need to put it anywhere
//else
void DetectorGeom::ConstructSDandField()
{
	//setting up magentic field
	fMagneticField = new MagneticField();
  	fFieldMgr = new G4FieldManager();
  	fFieldMgr->SetDetectorField(fMagneticField);
  	fFieldMgr->CreateChordFinder(fMagneticField);
  	G4bool forceToAllDaughters = false;
  	logicMagTube->SetFieldManager(fFieldMgr, forceToAllDaughters);

	//seting the sensitive detector, in this case it is the PMMA for now
	G4Region* detectorPmma=new G4Region("detectorPmma");
	detectorPmma->AddRootLogicalVolume(logicPmma);
	G4VisAttributes* pmmAtt=new G4VisAttributes(G4Color(0.5,0.5,1));
	logicPmma->SetVisAttributes(pmmAtt);
	G4String SDname;
	G4String HCname;
	TrackerSD* sensitive=new TrackerSD(SDname="active",HCname="HC_Pmma");
	G4SDManager* sdman=G4SDManager::GetSDMpointer();
	sdman->AddNewDetector(sensitive);
	logicPmma->SetSensitiveDetector(sensitive);



}
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
//function that is called to update the geometry if something is changed on the run time.
void DetectorGeom::UpdateGeometry()
{
	G4RunManager::GetRunManager()->DefineWorldVolume(ConstructWorld());
	G4RunManager::GetRunManager()->PhysicsHasBeenModified();
	G4RegionStore::GetInstance()->UpdateMaterialList(physWorld);
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}