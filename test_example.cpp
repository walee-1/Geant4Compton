#include "detector.hh"
#include "particle_gun.hh" //if you want to use a particle gun directly 
#include "particle_src.hh"
#include "G4RunManager.hh"
#include "physicsList.hh"
//#include "Randomize.hh"  //random number generator
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
//#include "G4UIterminal.hh" 
//UI terminal control
//#include "G4MTRunManager.hh" //if we ever want to use multi threaded run manager
#include "N01PrimaryGeneratorAction.hh"
#include <iostream>


int main(int argc, char** argv)
{
	if(std::remove("output.txt")<0){
		std::cout<<"A new output file will be written, woohoo!"<<std::endl;	
	}
	else std::cout<<"You dare run this program whilst an output.txt already exists?"<<
	" Now watch your kingdom engulf in flame as I lay waste to what"
	<< " you once recorded."<<std::endl;
	G4UIExecutive* ui=0;
	if(argc==1){
		ui=new G4UIExecutive(argc,argv);
	}
	//set up the run manager
	G4RunManager* runManager= new G4RunManager;
	//runManager->SetNumberOfThreads(1);

	//detector construction
	DetectorGeom* detector=new DetectorGeom();
	runManager->SetUserInitialization(detector);
	
	//physics initialization && physics list 
	//G4VModularPhysicsList* physicsList=new QBBC;
	//G4PhysListFactory factory;
	//G4VModularPhysicsList* physList=factory.ReferencePhysList();
	G4VUserPhysicsList* physics = new physicsList;
	runManager->SetUserInitialization(physics);
	//runManager->SetUserInitialization(physList);
	//particle source initialization

	//Primary Generator Action
	G4VUserPrimaryGeneratorAction* myAction=new GenParticleSource;
	runManager->SetUserAction(myAction);
	
	// visualization manager
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
	G4UImanager* UImanager= G4UImanager::GetUIpointer();
	//if you send a command with the execution of the binary
	if(!ui){
		G4String command="/control/execute ";
		G4String fileName=argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
	//if you can just want to use vis.mac
	else {
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
		delete ui;
	}
	//free up memory
	delete runManager;

	return 0;



// 		G4UImanager* UImanager = G4UImanager::GetUIpointer();
// 		G4UIExecutive* ui = 0;
// 	if ( ! ui ) { 
//     // batch mode
//     G4String command = "/control/execute ";
//     G4String fileName = argv[1];
//     UImanager->ApplyCommand(command+fileName);
//   }



	//~ if(argc==1)
	//~ {
		//~ G4UIsession * session = new G4UIterminal;
		//~ UI->ApplyCommand("/control/execute prerun.g4mac");
		//~ session->SessionStart();
		//~ delete session;
	//~ }
	//~ else
	//~ {
		//~ G4String command = "/control/execute ";
		//~ G4String fileName=argv[1];
		//~ UI->ApplyCommand(command+fileName);
	//~ }
	//~ delete visManager;
	
	// runManager->Initialize();
	// G4UImanager* UI = G4UImanager::GetUIpointer();
	// UI->ApplyCommand("/run/verbose 1");
	// UI->ApplyCommand("/event/verbose 1");
	// UI->ApplyCommand("/tracking/verbose 1");
	
	// runManager->BeamOn(30);
	// delete runManager;
}
